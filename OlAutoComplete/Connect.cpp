/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "stdafx.h"
#include "Connect.h"
#include "RowSet.h"
#include "NicknameCache.h"
#include "NicknamesView.h"
#include "dprintf.h"
#include "Resload.h"

//
// Steps that Outlook.exe does with NK2:
//
// buf = GlobalAlloc()
// buf = GlobalLock(ptr)
// ReadFile(buf)
// GlobalUnlock(buf)
// stream = CreateStreamOnHGlobal(buf)
// stream->Read_DWORD					// check for header 0xBAADF00D
// stream->Read_DWORD					// checks for 0x0000000A
// stream->Read_DWORD					// seems version
// stream->Read SRowset (num of rows)
// stream->Read all SRow's to MEM_ADDR
// stream->Read_DWORD					// 0? 
// stream->Read_DWORD*2					// Seems extrainformation according to NK2 spec
// GlobalFree(buf)
// MEM_ADDR -> this+0x24 ---> points to SRowSet

// ---------------------------------------------------------------------------

__declspec (thread) int g_stBytesRead;						// Counts  NK2 read sequence bytes
static void*			g_pRowSet;							// Pointer to in-memory rowset struct
NicknameCache*			CConnect::m_nickNameCache = nullptr;
static IStream*			g_pIStreamNamecache = nullptr;
const size_t			NK2_METADATA_SIZE	= 12;

// ---------------------------------------------------------------------------
CNktHookLib::HOOK_INFO g_hookInfo[8] = {0};
const int HOOK_ENTRY_CREATESTREAMONHGLOBAL = 0;
const int HOOK_ENTRY_STREAMREAD		       = 1;
const int HOOK_ENTRY_STREAMRELEASE		   = 2;
static CNktHookLib g_hookLib;
// ---------------------------------------------------------------------------

typedef long (NTAPI * PFNNTQUERYINFORMATIONFILE)(HANDLE,PIO_STATUS_BLOCK,PVOID,ULONG,FILE_INFORMATION_CLASS);
typedef HRESULT (WINAPI * PFNCREATESTREAMONHGLOBAL)(HGLOBAL,BOOL,LPSTREAM*);
typedef HRESULT (__stdcall * PFNISTREAMREAD)(LPSTREAM,  void *,ULONG,ULONG *);

// ---------------------------------------------------------------------------
// Returns true if HGLOBAL points to a NK2 autocomplete file on memory
// ---------------------------------------------------------------------------
static bool IsNK2FileBuffer(HGLOBAL hGlobal) {
	// Check for signature
	DWORD* pBuffer = (DWORD*) *((DWORD*)hGlobal); //dereference
	if (!pBuffer)
		return false;

	DWORD signature    = *pBuffer;
	DWORD majorVersion = *(pBuffer + 1);
	DWORD minorVersion = *(pBuffer + 2);
	return (signature == 0xBAADF00D && majorVersion == 0xA && minorVersion == 1) ;
}

// ---------------------------------------------------------------------------
// IStream::Release hook entry
// ---------------------------------------------------------------------------
static ULONG STDMETHODCALLTYPE _IStreamRelease(IStream* pThis) {
	if (pThis == g_pIStreamNamecache) {
		CConnect::m_nickNameCache = new NicknameCache(g_pRowSet);
	}
	return pThis->Release();
}

// ---------------------------------------------------------------------------
// IStream::Read hook entry
// ---------------------------------------------------------------------------
static HRESULT STDMETHODCALLTYPE _IStreamRead(IStream *pThis, void *pv,ULONG cb,ULONG *pcbRead) {
	
	static DWORD cNumRows = 0xffffffff;

	HRESULT hr = pThis->Read(pv, cb, pcbRead);
	if (pThis == g_pIStreamNamecache) {
		if (g_stBytesRead == NK2_METADATA_SIZE) {
			// We are after the metadata header, now read what many rows we got
			
			if (SUCCEEDED(hr)) {
				cNumRows = *((DWORD*) pv);
			}	
			// We are ready to read into the SRowSet structure
			// In Outlook 2007, at this point we are into the function that reads all the rows.
			// Traverse the EBP chain to get the SRowSet* parameter,which is the buffer we are 
			// interested on.

			_asm {
				push eax
				mov eax, [ebp]
				mov eax, [eax+0xC]
				mov g_pRowSet, eax
				pop eax
			}			
		}
		else if (g_stBytesRead == cNumRows * sizeof(SRow) + 4) {
			// We got the file read.
			// Now just wait the Stream release.

			g_hookLib.Unhook(g_hookInfo[HOOK_ENTRY_STREAMREAD].nHookId);
			g_hookLib.EnableHook(g_hookInfo[HOOK_ENTRY_STREAMRELEASE].nHookId, TRUE);
		}
		g_stBytesRead += cb;
	}
	return hr;
}

// ---------------------------------------------------------------------------
// CreateStreamOnHGlobal hook entry
// ---------------------------------------------------------------------------
static HRESULT WINAPI _CreateStreamOnHGlobal(
	_In_  HGLOBAL  hGlobal,
	_In_  BOOL     fDeleteOnRelease,
	_Out_ LPSTREAM *ppstm ) 
{
	HRESULT hr = PFNCREATESTREAMONHGLOBAL(g_hookInfo[HOOK_ENTRY_CREATESTREAMONHGLOBAL].lpCallOriginal)
		(hGlobal, fDeleteOnRelease, ppstm);

	if (SUCCEEDED(hr) && hGlobal && IsNK2FileBuffer(hGlobal)) {
		if (g_hookInfo[HOOK_ENTRY_STREAMREAD].nHookId != 0 )
			__debugbreak(); // it's supposed to enter this ONCE.
		//
		// We are interested on this interface which will be used to read
		// from the stream to the internal auto complete buffer
		//
		size_t* lpIStreamVtbl = (size_t*)(*(size_t*) *ppstm);		
		g_stBytesRead = 0;
		g_pIStreamNamecache = *ppstm;

		g_hookLib.Hook(&g_hookInfo[HOOK_ENTRY_STREAMREAD].nHookId,
			&g_hookInfo[HOOK_ENTRY_STREAMREAD].lpCallOriginal,  
			(void*)(lpIStreamVtbl[3]),
			_IStreamRead, 
			NKTHOOKLIB_DisallowReentrancy);				

		g_hookLib.Hook(&g_hookInfo[HOOK_ENTRY_STREAMRELEASE].nHookId,
			&g_hookInfo[HOOK_ENTRY_STREAMRELEASE].lpCallOriginal,  
			(void*)(lpIStreamVtbl[2]),
			_IStreamRelease, 
			NKTHOOKLIB_DisallowReentrancy);	
	}
	return hr;
}

// ---------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnect::OnConnection(LPDISPATCH Application, ext_ConnectMode ConnectMode, LPDISPATCH AddInInst, SAFEARRAY * * custom)
{
	FARPROC pCreateStreamOnHGlobal = GetProcAddress(GetModuleHandle(L"ole32.dll"), "CreateStreamOnHGlobal");
	assert(pCreateStreamOnHGlobal);
	g_hookLib.Hook(&g_hookInfo[HOOK_ENTRY_CREATESTREAMONHGLOBAL].nHookId, 
		&g_hookInfo[HOOK_ENTRY_CREATESTREAMONHGLOBAL].lpCallOriginal, 
		pCreateStreamOnHGlobal,
		_CreateStreamOnHGlobal, 
		NKTHOOKLIB_DisallowReentrancy);

	return S_OK;
}

// ---------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnect::raw_GetCustomUI(BSTR RibbonID, BSTR* RibbonXml) {
	if(!RibbonXml)
		return E_POINTER;
	*RibbonXml =  GetXMLResource(IDR_XML1);
	return S_OK;
}

// ---------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnect::ButtonClicked(IDispatch* pRibbon) {
		if (m_nickNameCache == nullptr) {
		MessageBox(::GetActiveWindow(), L"Autocomplete stream not available.", L"Error",MB_OK|MB_ICONEXCLAMATION);
	} else {
		CNicknamesView v(m_nickNameCache);
		v.DoModal();
	}
	return S_OK;
}

// ---------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CConnect::Invoke(DISPID dispidMember, 
    const IID &riid, 
    LCID lcid, 
    WORD wFlags, 
    DISPPARAMS *pdispparams, 
    VARIANT *pvarResult, 
    EXCEPINFO *pexceptinfo, 
    UINT *puArgErr)
{
    HRESULT hr = DISP_E_MEMBERNOTFOUND;
    if(dispidMember== DISPID_RIBBONBUTTONCLICK)
    {
        hr  = IDispatchImpl<IRibbonCallback, &__uuidof(IRibbonCallback)>::Invoke(dispidMember, 
            riid, 
            lcid, 
            wFlags,       
            pdispparams, 
            pvarResult, 
            pexceptinfo, 
            puArgErr);
    }
    if (DISP_E_MEMBERNOTFOUND == hr)
        hr = IDispatchImpl<_IDTExtensibility2, &__uuidof(_IDTExtensibility2), &LIBID_AddInDesignerObjects,1>::Invoke(dispidMember, 
            riid, 
            lcid, 
            wFlags, 
            pdispparams, 
            pvarResult, 
            pexceptinfo, 
            puArgErr);
    return hr;
}