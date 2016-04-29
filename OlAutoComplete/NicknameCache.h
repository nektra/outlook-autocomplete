/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#pragma once
#include <windows.h>
#include "rowset.h"

class NicknameCache
{
public:
	NicknameCache(void* pBuffer);
	~NicknameCache(void);
	int			GetCount() const;
	SRow*		GetRow(int i) const;
	bool		GetPropValue(int row, DWORD propidx, SPropValue& val);
	void		SetPropValue(int row, SPropValue& val);
	void		SwapRows(int r0, int r1);
	void		SortByTag(DWORD propTag);
private:
	NicknameCache& operator=(NicknameCache&);
	NicknameCache(NicknameCache&);
	CRITICAL_SECTION		m_cs;
	SRowSet*				m_pRowset;
};

