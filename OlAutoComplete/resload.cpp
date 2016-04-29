/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "stdafx.h"
#include "resload.h"

HRESULT HrGetResource(int nId, 
    LPCTSTR lpType, 
    LPVOID* ppvResourceData,       
    DWORD* pdwSizeInBytes)
{
    HMODULE hModule = ATL::_AtlBaseModule.GetModuleInstance();
    if (!hModule)
        return E_UNEXPECTED;
    HRSRC hRsrc = FindResource(hModule, MAKEINTRESOURCE(nId), lpType);
    if (!hRsrc)
        return HRESULT_FROM_WIN32(GetLastError());
    HGLOBAL hGlobal = LoadResource(hModule, hRsrc);
    if (!hGlobal)
        return HRESULT_FROM_WIN32(GetLastError());
    *pdwSizeInBytes = SizeofResource(hModule, hRsrc);
    *ppvResourceData = LockResource(hGlobal);
    return S_OK;
}

BSTR GetXMLResource(int nId)
{
    LPVOID pResourceData = NULL;
    DWORD dwSizeInBytes = 0;
    HRESULT hr = HrGetResource(nId, TEXT("XML"), 
        &pResourceData, &dwSizeInBytes);
    if (FAILED(hr))
        return NULL;
    // Assumes that the data is not stored in Unicode.
    ATL::CComBSTR cbstr(dwSizeInBytes, reinterpret_cast<LPCSTR>(pResourceData));
    return cbstr.Detach();
}

SAFEARRAY* GetOFSResource(int nId)
{
    LPVOID pResourceData = NULL;
    DWORD dwSizeInBytes = 0;
    if (FAILED(HrGetResource(nId, TEXT("OFS"), 
        &pResourceData, &dwSizeInBytes)))
        return NULL;
    SAFEARRAY* psa;
    SAFEARRAYBOUND dim = {dwSizeInBytes, 0};
    psa = SafeArrayCreate(VT_UI1, 1, &dim);
    if (psa == NULL)
        return NULL;
    BYTE* pSafeArrayData;
    SafeArrayAccessData(psa, (void**)&pSafeArrayData);
    memcpy((void*)pSafeArrayData, pResourceData, dwSizeInBytes);
    SafeArrayUnaccessData(psa);
    return psa;
}