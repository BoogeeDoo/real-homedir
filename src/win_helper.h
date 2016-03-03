#if defined(_WIN32)
#include <assert.h>
#include <direct.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

#include "uv.h"

#include <winsock2.h>
#include <winperf.h>
#include <iphlpapi.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <windows.h>
#include <userenv.h>

int WHUtf16ToUtf8(const WCHAR* utf16Buffer, size_t utf16Size, char* utf8Buffer, size_t utf8Size);
int WHTranslateSysError(int sys_errno);
#endif