#pragma once
/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

HRESULT HrGetResource(int nId, 
    LPCTSTR lpType, 
    LPVOID* ppvResourceData,       
    DWORD* pdwSizeInBytes);

BSTR GetXMLResource(int nId);

SAFEARRAY* GetOFSResource(int nId);