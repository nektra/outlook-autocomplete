/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#include "resource.h"       // main symbols
#include "OlAutoComplete_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;
using namespace Office;
class NicknameCache;

// CConnect
extern _ATL_FUNC_INFO FuncInfoOnClickButton;

class ATL_NO_VTABLE CConnect :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConnect, &CLSID_Connect>,
	public IDispatchImpl<IConnect, &IID_IConnect, &LIBID_NktOlAutoCompleteLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<_IDTExtensibility2, &__uuidof(_IDTExtensibility2), &LIBID_AddInDesignerObjects, /* wMajor = */ 1>,
	public IDispatchImpl<IRibbonExtensibility, &__uuidof(IRibbonExtensibility), &__uuidof(__Office), /* wMajor = */ 2, /* wMinor = */ 5>,
	public IDispatchImpl<IRibbonCallback, &__uuidof(IRibbonCallback)>,
	public IDispEventSimpleImpl<1,CConnect,&__uuidof(Office::_CommandBarButtonEvents)> 
{
public:
	CConnect()
	{
	}
	DECLARE_REGISTRY_RESOURCEID(IDR_CONNECT)

	BEGIN_COM_MAP(CConnect)
		COM_INTERFACE_ENTRY2(IDispatch, IRibbonCallback)
		COM_INTERFACE_ENTRY(IConnect)
		COM_INTERFACE_ENTRY2(IDispatch, _IDTExtensibility2)
		COM_INTERFACE_ENTRY(_IDTExtensibility2)
		COM_INTERFACE_ENTRY(IRibbonExtensibility)
	END_COM_MAP()
	BEGIN_SINK_MAP(CConnect)
	END_SINK_MAP()
	
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct(){
		
		return S_OK;
	}

	void FinalRelease()	{
	}

public:

		// _IDTExtensibility2 Methods
public:
	STDMETHOD(OnConnection)(LPDISPATCH Application, ext_ConnectMode ConnectMode, LPDISPATCH AddInInst, SAFEARRAY * * custom);
	STDMETHOD(OnDisconnection)(ext_DisconnectMode RemoveMode, SAFEARRAY * * custom)	{ return S_OK; }
	STDMETHOD(OnAddInsUpdate)(SAFEARRAY * * custom)		{ return S_OK;	}
	STDMETHOD(OnStartupComplete)(SAFEARRAY * * custom)	{ return S_OK;  }
	STDMETHOD(OnBeginShutdown)(SAFEARRAY * * custom)	{ return S_OK;  }

	STDMETHOD(raw_GetCustomUI)(BSTR RibbonID, BSTR * RibbonXml);
	STDMETHOD(ButtonClicked)(IDispatch* ribbon);
	STDMETHOD(Invoke)(DISPID dispidMember, 
    const IID &riid, 
    LCID lcid, 
    WORD wFlags, 
    DISPPARAMS *pdispparams, 
    VARIANT *pvarResult, 
    EXCEPINFO *pexceptinfo, 
    UINT *puArgErr);

	static NicknameCache* m_nickNameCache;
private:

	Office::CommandBarControlPtr m_ctl;
};

OBJECT_ENTRY_AUTO(__uuidof(Connect), CConnect)
