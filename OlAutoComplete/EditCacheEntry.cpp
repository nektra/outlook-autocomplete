// EditCacheEntry.cpp : Implementation of CEditCacheEntry

#include "stdafx.h"
#include "EditCacheEntry.h"
#include "nk2props.h"
#include <algorithm>

LRESULT CEditCacheEntry::OnEnChangeEditweight(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	return 0;
}

void CEditCacheEntry::SetSourceRow(int i) {
	m_rowIndex = i;
	UpdateControls();
}

void CEditCacheEntry::UpdateControls() {
	SPropValue sval;
	m_nickNameCache->GetPropValue(m_rowIndex, PR_NICK_NAME_W, sval);
	SetDlgItemText(IDC_EDIT_NICKNAME, sval.Value.lpszW);

	m_nickNameCache->GetPropValue(m_rowIndex, PR_DROPDOWN_DISPLAY_NAME_W, sval);
	SetDlgItemText(IDC_EDIT_DISPLAYAS, sval.Value.lpszW);

	m_nickNameCache->GetPropValue(m_rowIndex, PR_EMAIL_ADDRESS_W, sval);
	SetDlgItemText(IDC_EDIT_EMAILADDR, sval.Value.lpszW);

	m_nickNameCache->GetPropValue(m_rowIndex, PR_NICKNAME_WEIGHT, sval);
	wchar_t buf[10];
	wsprintf(buf, L"%d", sval.Value.l);
	SetDlgItemInt(IDC_EDIT_WEIGHT, sval.Value.l, FALSE);
}

LRESULT CEditCacheEntry::OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	BOOL ok;
	UINT weight = GetDlgItemInt(IDC_EDIT_WEIGHT, &ok);
	if (!ok){
		MessageBox(L"Enter a proper weight value.");
		return 1;
	}

	BSTR strDisplayAs = nullptr;
	BSTR strAddress = nullptr;
	BSTR strNickname = nullptr;
	SysAllocStringLen(strDisplayAs, 1024);
	SysAllocStringLen(strAddress,   1024);
	SysAllocStringLen(strNickname,  1024);
	GetDlgItemText(IDC_EDIT_DISPLAYAS, strDisplayAs);
	GetDlgItemText(IDC_EDIT_EMAILADDR, strAddress);
	GetDlgItemText(IDC_EDIT_NICKNAME,  strNickname);

	SPropValue sval;
	sval.dwAlignPad = 0xbaadf00d;
	sval.ulPropTag  = PR_NICKNAME_WEIGHT;
	sval.Value.l	= weight;
	m_nickNameCache->SetPropValue(m_rowIndex, sval);

	sval.ulPropTag		= PR_DROPDOWN_DISPLAY_NAME_W;
	sval.Value.lpszW	= strDisplayAs;
	m_nickNameCache->SetPropValue(m_rowIndex, sval);

	sval.ulPropTag		= PR_NICK_NAME_W;
	sval.Value.lpszW	= strNickname;
	m_nickNameCache->SetPropValue(m_rowIndex, sval);

	sval.ulPropTag		= PR_EMAIL_ADDRESS_W;
	sval.Value.lpszW	= strAddress;
	m_nickNameCache->SetPropValue(m_rowIndex, sval);

	EndDialog(wID);
	return 0;
}

