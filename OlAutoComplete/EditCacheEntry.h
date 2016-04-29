/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#pragma once

#include "resource.h"       // main symbols
#include "rowset.h"
#include "NicknameCache.h"
#include <atlhost.h>

using namespace ATL;

// CEditCacheEntry

class CEditCacheEntry : public CAxDialogImpl<CEditCacheEntry>
{
public:
	CEditCacheEntry(NicknameCache* pCache, int rowIndex) : m_nickNameCache(pCache), m_rowIndex(rowIndex) {
	}
	~CEditCacheEntry() 	{}

	enum { IDD = IDD_EDITCACHEENTRY };

BEGIN_MSG_MAP(CEditCacheEntry)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
	CHAIN_MSG_MAP(CAxDialogImpl<CEditCacheEntry>)
END_MSG_MAP()


	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CAxDialogImpl<CEditCacheEntry>::OnInitDialog(uMsg, wParam, lParam, bHandled);
		bHandled = TRUE;
		UpdateControls();
		return 1;  // Let the system set the focus
	}

	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
		EndDialog(wID);
		return 0;
	}
	LRESULT OnEnChangeEdit1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEnChangeEditweight(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	void SetSourceRow(int index);
private:
	NicknameCache* m_nickNameCache;
	void UpdateControls();
	int m_rowIndex;
};


