#include "stdafx.h"
#include "NicknameCache.h"
#include <algorithm>

NicknameCache::NicknameCache(void* pBuffer) {
	InitializeCriticalSection(&m_cs);
	m_pRowset = reinterpret_cast<SRowSet*>(*((size_t*) pBuffer));
}

NicknameCache::~NicknameCache(void){
	DeleteCriticalSection(&m_cs);
}

int NicknameCache::GetCount() const {
	return m_pRowset->cRows;
}

SRow* NicknameCache::GetRow(int i) const {
	assert(i < GetCount());
	return &m_pRowset->aRow[i];
}

bool NicknameCache::GetPropValue(int row, DWORD proptag, SPropValue& val) {
	assert(row < GetCount());
	SRow srow = m_pRowset->aRow[row];
	for (int i = 0; i < (int)srow.cValues; ++i) {
		if (srow.lpProps[i].ulPropTag == proptag) {
			val = srow.lpProps[i];
			return true;
		}
	}
	return false;
}

void NicknameCache::SetPropValue(int row, SPropValue& val) {
	assert(row < GetCount());
	SRow srow = m_pRowset->aRow[row];
	for (int i = 0; i < (int)srow.cValues; ++i) {
		if (srow.lpProps[i].ulPropTag == val.ulPropTag) {
			srow.lpProps[i] = val;
		}
	}
}

void NicknameCache::SwapRows(int r0, int r1) {
	SRow* s0 = GetRow(r0);
	SRow* s1 = GetRow(r1);
	SRow st;
	st.cValues = s0->cValues;
	st.lpProps = s0->lpProps;
	m_pRowset->aRow[r0].cValues = s1->cValues;
	m_pRowset->aRow[r0].lpProps	= s1->lpProps;
	m_pRowset->aRow[r1].cValues = st.cValues;
	m_pRowset->aRow[r1].lpProps = st.lpProps;
}

void NicknameCache::SortByTag(DWORD propTag) {
	int cValues = m_pRowset->cRows;
	SRow* sr = m_pRowset->aRow;
	std::sort(sr, sr + cValues, 
		[propTag](const SRow &s1, const SRow &s2) {
			SPropValue* sv1 = std::find_if(s1.lpProps, s1.lpProps + s1.cValues, [propTag](const SPropValue& sv) {
				return sv.ulPropTag == propTag;
			});
			SPropValue* sv2 = std::find_if(s2.lpProps, s2.lpProps + s2.cValues, [propTag](const SPropValue& sv) {
				return sv.ulPropTag == propTag;
			});
			return sv1->Value.l > sv2->Value.l;
	});
}