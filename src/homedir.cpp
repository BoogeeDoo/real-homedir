/*
 * =====================================================================================
 *
 *       Filename:  homedir.cpp
 *
 *    Description:  Getting home dir
 *
 *        Version:  1.0
 *        Created:  2016/03/03 17时01分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  XadillaX (ZKD), zhukaidi@souche.com
 *   Organization:  Design & Development Center, Souche Car Service Co., Ltd, HANGZHOU
 *
 * =====================================================================================
 */
#include <nan.h>
#include <uv.h>

#if defined(_WIN32)

// -- WIN32
#include "win_helper.h"
#include <userenv.h>
// -- WIN32

#else

// -- UNIX
#include <stddef.h> /* NULL */
#include <stdio.h> /* printf */
#include <stdlib.h>
#include <string.h> /* strerror */
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <limits.h> /* INT_MAX, PATH_MAX, IOV_MAX */
#include <sys/uio.h> /* writev */
#include <sys/resource.h> /* getrusage */
#include <pwd.h>

#ifdef __linux__
# include <sys/ioctl.h>
#endif

#ifdef __sun
# include <sys/types.h>
# include <sys/wait.h>
#endif

#ifdef __APPLE__
# include <mach-o/dyld.h> /* _NSGetExecutablePath */
# include <sys/filio.h>
# include <sys/ioctl.h>
#endif

#if defined(__FreeBSD__) || defined(__DragonFly__)
# include <sys/sysctl.h>
# include <sys/filio.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# define UV__O_CLOEXEC O_CLOEXEC
# if defined(__FreeBSD__) && __FreeBSD__ >= 10
#  define uv__accept4 accept4
#  define UV__SOCK_NONBLOCK SOCK_NONBLOCK
#  define UV__SOCK_CLOEXEC  SOCK_CLOEXEC
# endif
# if !defined(F_DUP2FD_CLOEXEC) && defined(_F_DUP2FD_CLOEXEC)
#  define F_DUP2FD_CLOEXEC  _F_DUP2FD_CLOEXEC
# endif
#endif

#ifdef _AIX
#include <sys/ioctl.h>
#endif

#if defined(__ANDROID_API__) && __ANDROID_API__ < 21
# include <dlfcn.h>  /* for dlsym */
#endif

void __free(void* buf)
{
    if(buf)
    {
        free(buf);
        buf = 0;
    }
}
// -- UNIX

#endif

int __GetTrueHomeDir(char* buffer, size_t* size)
{
#if defined(_WIN32)
    // refer https://github.com/libuv/libuv/blob/2606ba22a7012d0ed0ebb4464eec8fca9042c51e/src/win/util.c#L1171
    // and delete checking USERPROFILE environment
    HANDLE token;
    DWORD bufsize;
    wchar_t path[MAX_PATH];
    int r;

    if(OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &token) == 0)
    {
        return WHTranslateSysError(GetLastError());
    }

    bufsize = MAX_PATH;
    if(!GetUserProfileDirectoryW(token, path, &bufsize))
    {
        r = GetLastError();
        CloseHandle(token);

        /*  This should not be possible */
        if(r == ERROR_INSUFFICIENT_BUFFER)
        {
            return UV_EIO;
        }

        return WHTranslateSysError(r);
    }

    CloseHandle(token);

    /*  Check how much space we need */
    bufsize = WHUtf16ToUtf8(path, -1, NULL, 0);
    if(bufsize == 0)
    {
        return WHTranslateSysError(GetLastError());
    }
    else
    if(bufsize > *size)
    {
        *size = bufsize;
        return UV_ENOBUFS;
    }

    /*  Convert to UTF-8 */
    bufsize = WHUtf16ToUtf8(path, -1, buffer, *size);
    if(bufsize == 0)
    {
        return WHTranslateSysError(GetLastError());
    }

    *size = bufsize - 1;
    return 0;
#else
    // refer https://github.com/libuv/libuv/blob/2606ba22a7012d0ed0ebb4464eec8fca9042c51e/src/unix/core.c#L1016
    // and delete checking HOME environment

    struct passwd pw;
    struct passwd* result;
    char* buf = NULL;
    uid_t uid;
    size_t bufsize;
    size_t len;
    long initsize;
    int r;

#if defined(__ANDROID_API__) && __ANDROID_API__ < 21
    int (*getpwuid_r)(uid_t, struct passwd*, char*, size_t, struct passwd**);
#endif

    if(buffer == NULL || size == NULL || *size == 0)
    {
        return -EINVAL;
    }

#if defined(__ANDROID_API__) && __ANDROID_API__ < 21
    getpwuid_r = dlsym(RTLD_DEFAULT, "getpwuid_r");
    if(getpwuid_r == NULL)
    {
        return -ENOSYS;
    }
#endif

    /*  HOME is not set, so call getpwuid() */
    initsize = sysconf(_SC_GETPW_R_SIZE_MAX);

    if(initsize <= 0) bufsize = 4096;
    else bufsize = (size_t)initsize;

    uid = getuid();
    buf = NULL;

    for(;;)
    {
        __free(buf);
        buf = (char*)malloc(bufsize);

        if(buf == NULL) return -ENOMEM;

        r = getpwuid_r(uid, &pw, buf, bufsize, &result);

        if(r != ERANGE) break;
        bufsize *= 2;
    }

    if(r != 0)
    {
        __free(buf);
        return -r;
    }

    if(result == NULL)
    {
        __free(buf);
        return -ENOENT;
    }

    len = strlen(pw.pw_dir);

    if(len >= *size)
    {
        *size = len + 1;
        __free(buf);
        return -ENOBUFS;
    }

    memcpy(buffer, pw.pw_dir, len + 1);
    *size = len;
    __free(buf);

    return 0;
#endif
}
