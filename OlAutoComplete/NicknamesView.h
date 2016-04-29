/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#include "resource.h"       // main symbols
#include <atlhost.h>

using namespace ATL;
class NicknameCache;
class CNicknamesView : public CAxDialogImpl<CNicknamesView> {
public:
	CNicknamesView(NicknameCache* pCache){
		m_nicknameCache = pCache;
	}

	~CNicknamesView() {	}

	enum { IDD = IDD_NICKNAMESVIEW };

	BEGIN_MSG_MAP(CNicknamesView)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
		COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
		CHAIN_MSG_MAP(CAxDialogImpl<CNicknamesView>)
		NOTIFY_HANDLER(IDC_NICKNAMES, LVN_GETDISPINFO, OnLvnGetdispinfoNicknames)
		NOTIFY_HANDLER(IDC_NICKNAMES, NM_DBLCLK, OnNMDblclkNicknames)
		COMMAND_HANDLER(IDC_EDITENTRY, BN_CLICKED, OnBnClickedEditentry)
		COMMAND_HANDLER(IDC_MOVEUP, BN_CLICKED, OnBnClickedMoveup)
		COMMAND_HANDLER(IDC_MOVEDOWN, BN_CLICKED, OnBnClickedMovedown)
		COMMAND_HANDLER(IDC_SORTLIST, BN_CLICKED, OnBnClickedSortlist)
		NOTIFY_HANDLER(IDC_NICKNAMES, LVN_ITEMCHANGED, OnLvnItemchangedNicknames)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnLvnGetdispinfoNicknames(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnNMDblclkNicknames(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnBnClickedEditentry(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedMoveup(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedMovedown(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedSortlist(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
	NicknameCache* m_nicknameCache;

	void FillNickNameList();
	void SetupControls();
public:

	LRESULT OnLvnItemchangedNicknames(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
};


