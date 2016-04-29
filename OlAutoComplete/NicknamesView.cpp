/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "stdafx.h"
#include "NicknamesView.h"
#include "NicknameCache.h"
#include "nk2props.h"
#include "EditCacheEntry.h"
#include "dprintf.h"

//
// Columns definition
//
struct ListColumn {
	wchar_t *	headerText;
	int			width;
};

static const ListColumn g_lvCols[] = {
	L"Nickname", 150,
	L"Address", 150,
	L"Display as", 200,
	L"Weight", 150
};

LRESULT CNicknamesView::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	CAxDialogImpl<CNicknamesView>::OnInitDialog(uMsg, wParam, lParam, bHandled);
	bHandled = TRUE;

	SetupControls();
	FillNickNameList();

	return 1;  // Let the system set the focus
}

LRESULT CNicknamesView::OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
	EndDialog(wID);
	return 0;
}

LRESULT CNicknamesView::OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
	EndDialog(wID);
	return 0;
}

void CNicknamesView::SetupControls() {
	HWND hList = GetDlgItem(IDC_NICKNAMES).m_hWnd;
	ListView_SetView(hList, LV_VIEW_LIST);

	for (int i = 0; i < _countof(g_lvCols); ++i) {
		LVCOLUMN lv = { 0 };
		lv.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lv.fmt = LVCFMT_LEFT;
		lv.iSubItem = i;
		lv.pszText = g_lvCols[i].headerText;
		lv.cchTextMax = lstrlen(lv.pszText);
		lv.cx = g_lvCols[i].width;
		ListView_InsertColumn(hList, i, &lv);
	}
}

void CNicknamesView::FillNickNameList() {
	HWND hList = GetDlgItem(IDC_NICKNAMES).m_hWnd;

	for (int i = 0; i < m_nicknameCache->GetCount(); ++i) {
		LVITEM lvi = {0};
		lvi.mask = LVIF_TEXT;
		lvi.iItem = i;	
		lvi.pszText = LPSTR_TEXTCALLBACK;
		ListView_InsertItem(hList, &lvi);
	}
}

LRESULT CNicknamesView::OnLvnGetdispinfoNicknames(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/) {
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	SPropValue sval = {0};
	wchar_t numbuf[40];
	switch (pDispInfo->item.iSubItem)
	{
	case 0:
		m_nicknameCache->GetPropValue(pDispInfo->item.iItem, PR_NICK_NAME_W, sval);		
		pDispInfo->item.cchTextMax = lstrlen(sval.Value.lpszW);
		pDispInfo->item.pszText = sval.Value.lpszW;	
		break;
	case 1:
		m_nicknameCache->GetPropValue(pDispInfo->item.iItem, PR_EMAIL_ADDRESS_W, sval);		
		pDispInfo->item.cchTextMax = lstrlen(sval.Value.lpszW);
		pDispInfo->item.pszText = sval.Value.lpszW;	
		break;
	case 2:
		m_nicknameCache->GetPropValue(pDispInfo->item.iItem, PR_DROPDOWN_DISPLAY_NAME_W, sval);		
		pDispInfo->item.cchTextMax = lstrlen(sval.Value.lpszW);
		pDispInfo->item.pszText = sval.Value.lpszW;	
		break;
	case 3:
		m_nicknameCache->GetPropValue(pDispInfo->item.iItem, PR_NICKNAME_WEIGHT, sval);		
		pDispInfo->item.cchTextMax = sizeof(numbuf);
		wsprintf(numbuf, L"%d", sval.Value.l);
		pDispInfo->item.pszText = numbuf;
		break;
	default:
		break;
	}
	return TRUE;
}

LRESULT CNicknamesView::OnNMDblclkNicknames(int idCtrl, LPNMHDR pNMHDR, BOOL& /*bHandled*/) {
	HWND hList = GetDlgItem(IDC_NICKNAMES).m_hWnd;
	int i = ListView_GetNextItem(hList, -1, LVNI_SELECTED);

	if (i != -1) {
		CEditCacheEntry editDlg(m_nicknameCache,i);
		editDlg.DoModal();				
		ListView_DeleteAllItems(hList);
		FillNickNameList();
	}
	return 0;
}

LRESULT CNicknamesView::OnBnClickedEditentry(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	HWND hList = GetDlgItem(IDC_NICKNAMES).m_hWnd;
	int i = ListView_GetNextItem(hList, -1, LVNI_SELECTED);

	if (i != -1) {
		CEditCacheEntry editDlg(m_nicknameCache,i);
		editDlg.DoModal();		
		ListView_DeleteAllItems(hList);
		FillNickNameList();
	}
	return 0;
}


LRESULT CNicknamesView::OnBnClickedMoveup(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	HWND hList = GetDlgItem(IDC_NICKNAMES).m_hWnd;
	int i = ListView_GetNextItem(hList, -1, LVNI_SELECTED);

	if (i != -1) {
		m_nicknameCache->SwapRows(i, i-1);
		ListView_DeleteAllItems(hList);
		FillNickNameList();
	}
	return 0;
}

LRESULT CNicknamesView::OnBnClickedMovedown(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	HWND hList = GetDlgItem(IDC_NICKNAMES).m_hWnd;
	int i = ListView_GetNextItem(hList, -1, LVNI_SELECTED);

	if (i != -1) {
		m_nicknameCache->SwapRows(i, i+1);
		ListView_DeleteAllItems(hList);
		FillNickNameList();
	}
	return 0;
}

LRESULT CNicknamesView::OnBnClickedSortlist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	m_nicknameCache->SortByTag(PR_NICKNAME_WEIGHT);
	HWND hList = GetDlgItem(IDC_NICKNAMES).m_hWnd;
	ListView_DeleteAllItems(hList);
	FillNickNameList();
	return 0;
}

LRESULT CNicknamesView::OnLvnItemchangedNicknames(int idCtrl, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	HWND hList = GetDlgItem(IDC_NICKNAMES).m_hWnd;
	int i = ListView_GetNextItem(hList, -1, LVNI_SELECTED);

	int nameCount = m_nicknameCache->GetCount();
	
	::EnableWindow(GetDlgItem(IDC_EDITENTRY), i == -1 ? FALSE : TRUE);
	::EnableWindow(GetDlgItem(IDC_MOVEDOWN), (i == -1) || (i == nameCount-1) ? FALSE : TRUE);
	::EnableWindow(GetDlgItem(IDC_MOVEUP), (i == -1) || (i == 0) ? FALSE : TRUE);
	
	return 0;
}
