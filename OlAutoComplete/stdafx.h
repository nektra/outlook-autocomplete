#pragma once
/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifdef _M_IX86
#ifdef _DEBUG
#pragma comment (lib,"nkthooklib_debug.lib")
#else
#pragma comment (lib, "nkthooklib.lib")
#endif // _DEBUG
#endif // _M_IX86

#ifdef _M_X64
#ifdef _DEBUG
#pragma comment (lib,"nkthooklib64_debug.lib")
#else
#pragma comment (lib, "nkthooklib64.lib")
#endif // _DEBUG
#endif // _M_X64

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlwin.h>

// Addin Designer, Office and MSOutlook type libraries
#import "libid:AC0714F2-3D04-11D1-AE7D-00A0C90F26F4" raw_interfaces_only, raw_native_types, no_namespace, named_guids, auto_search
#import "libid:2DF8D04C-5BFA-101B-BDE5-00AA0044DE52" auto_rename 
#import "libid:00062FFF-0000-0000-C000-000000000046" auto_rename

#include <nkthooklib.h>
#include <winternl.h>
#include <strsafe.h>
