/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
class COLNICKSADDINModule : public ATL::CAtlDllModuleT< COLNICKSADDINModule >
{
public :
	DECLARE_LIBID(LIBID_NktOlAutoCompleteLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_OLNICKSADDIN, "{95452D9E-6A0A-4147-B63D-AECA67C1E4FB}")
};

extern class COLNICKSADDINModule _AtlModule;
