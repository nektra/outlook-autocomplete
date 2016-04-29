/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#pragma once

typedef struct _SBinary
{
	ULONG       cb;
	LPBYTE      lpb;
} SBinary, FAR *LPSBinary;

typedef struct _SShortArray
{
	ULONG       cValues;
	short int   FAR *lpi;
} SShortArray;

typedef struct _SGuidArray
{
	ULONG       cValues;
	GUID        FAR *lpguid;
} SGuidArray;

typedef struct _SRealArray
{
	ULONG       cValues;
	float       FAR *lpflt;
} SRealArray;

typedef struct _SLongArray
{
	ULONG       cValues;
	LONG        FAR *lpl;
} SLongArray;

typedef struct _SLargeIntegerArray
{
	ULONG       cValues;
	LARGE_INTEGER   FAR *lpli;
} SLargeIntegerArray;

typedef struct _SDateTimeArray
{
	ULONG       cValues;
	FILETIME    FAR *lpft;
} SDateTimeArray;

typedef struct _SAppTimeArray
{
	ULONG       cValues;
	double      FAR *lpat;
} SAppTimeArray;

typedef struct _SCurrencyArray
{
	ULONG       cValues;
	CURRENCY    FAR *lpcur;
} SCurrencyArray;

typedef struct _SBinaryArray
{
	ULONG       cValues;
	SBinary     FAR *lpbin;
} SBinaryArray;

typedef struct _SDoubleArray
{
	ULONG       cValues;
	double      FAR *lpdbl;
} SDoubleArray;

typedef struct _SWStringArray
{
	ULONG       cValues;
	LPWSTR      FAR *lppszW;
} SWStringArray;

typedef struct _SLPSTRArray
{
	ULONG       cValues;
	LPSTR       FAR *lppszA;
} SLPSTRArray;

typedef union _PV
{
	short int           i;       /* case PT_I2 */
	LONG                l;       /* case PT_LONG */
	ULONG               ul;      /* alias for PT_LONG */
	float               flt;     /* case PT_R4 */
	double              dbl;     /* case PT_DOUBLE */
	unsigned short int  b;       /* case PT_BOOLEAN */
	CURRENCY            cur;     /* case PT_CURRENCY */
	double              at;      /* case PT_APPTIME */
	FILETIME            ft;      /* case PT_SYSTIME */
	LPSTR               lpszA;   /* case PT_STRING8 */
	SBinary             bin;     /* case PT_BINARY */
	LPWSTR              lpszW;   /* case PT_UNICODE */
	LPGUID              lpguid;  /* case PT_CLSID */
	LARGE_INTEGER       li;      /* case PT_I8 */
	SShortArray         MVi;     /* case PT_MV_I2 */
	SLongArray          MVl;     /* case PT_MV_LONG */
	SRealArray          MVflt;   /* case PT_MV_R4 */
	SDoubleArray        MVdbl;   /* case PT_MV_DOUBLE */
	SCurrencyArray      MVcur;   /* case PT_MV_CURRENCY */
	SAppTimeArray       MVat;    /* case PT_MV_APPTIME */
	SDateTimeArray      MVft;    /* case PT_MV_SYSTIME */
	SBinaryArray        MVbin;   /* case PT_MV_BINARY */
	SLPSTRArray         MVszA;   /* case PT_MV_STRING8 */
	SWStringArray       MVszW;   /* case PT_MV_UNICODE */
	SGuidArray          MVguid;  /* case PT_MV_CLSID */
	SLargeIntegerArray  MVli;    /* case PT_MV_I8 */
	SCODE               err;     /* case PT_ERROR */
	LONG                x;       /* case PT_NULL,
								 PT_OBJECT (no usable value) */
} __UPV;
typedef struct _SPropValue
{
	ULONG ulPropTag;
	ULONG dwAlignPad;
	union _PV Value;
} SPropValue, FAR *LPSPropValue;

typedef struct _SRow
{
	ULONG ulAdrEntryPad;
	ULONG cValues;
	SPropValue* lpProps;
} SRow, FAR *LPSRow;

typedef struct _SRowSet
{
	ULONG cRows;
	SRow aRow[1];
} SRowSet, FAR *LPSRowSet;
