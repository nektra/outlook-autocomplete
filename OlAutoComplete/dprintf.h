/*
 *
 * Copyright (C) 2016 Nektra S.A
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#pragma once

inline void dprintf(const wchar_t * lpszFormat, ...) {
#ifdef _DEBUG
	const int MAX_MESSAGE = 1024;
	va_list args;
	va_start(args, lpszFormat);

	wchar_t szBuffer[MAX_MESSAGE];
	HRESULT hr = StringCchVPrintfW(szBuffer, MAX_MESSAGE, lpszFormat, args);
	assert(SUCCEEDED(hr));
	::OutputDebugStringW(szBuffer);
	va_end(args);
#endif
}
