/******************************************************************************
 * Quantitative Kit Library                                                   *
 *                                                                            *
 * Copyright (C) 2017 Xiaojun Gao                                             *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 ******************************************************************************/
#ifndef QK_ERRNO_H
#define QK_ERRNO_H

#include <errno.h>

#define QK__EOF     (-4095)
#define QK__UNKNOWN (-4094)

#define QK__EAI_ADDRFAMILY  (-3000)
#define QK__EAI_AGAIN       (-3001)
#define QK__EAI_BADFLAGS    (-3002)
#define QK__EAI_CANCELED    (-3003)
#define QK__EAI_FAIL        (-3004)
#define QK__EAI_FAMILY      (-3005)
#define QK__EAI_MEMORY      (-3006)
#define QK__EAI_NODATA      (-3007)
#define QK__EAI_NONAME      (-3008)
#define QK__EAI_OVERFLOW    (-3009)
#define QK__EAI_SERVICE     (-3010)
#define QK__EAI_SOCKTYPE    (-3011)
#define QK__EAI_BADHINTS    (-3013)
#define QK__EAI_PROTOCOL    (-3014)

/* Only map to the system errno on non-Windows platforms. It's apparently
 * a fairly common practice for Windows programmers to redefine errno codes.
 */
#if defined(E2BIG) && !defined(_WIN32)
# define QK__E2BIG (-E2BIG)
#else
# define QK__E2BIG (-4093)
#endif

#if defined(EACCES) && !defined(_WIN32)
# define QK__EACCES (-EACCES)
#else
# define QK__EACCES (-4092)
#endif

#if defined(EADDRINUSE) && !defined(_WIN32)
# define QK__EADDRINUSE (-EADDRINUSE)
#else
# define QK__EADDRINUSE (-4091)
#endif

#if defined(EADDRNOTAVAIL) && !defined(_WIN32)
# define QK__EADDRNOTAVAIL (-EADDRNOTAVAIL)
#else
# define QK__EADDRNOTAVAIL (-4090)
#endif

#if defined(EAFNOSUPPORT) && !defined(_WIN32)
# define QK__EAFNOSUPPORT (-EAFNOSUPPORT)
#else
# define QK__EAFNOSUPPORT (-4089)
#endif

#if defined(EAGAIN) && !defined(_WIN32)
# define QK__EAGAIN (-EAGAIN)
#else
# define QK__EAGAIN (-4088)
#endif

#if defined(EALREADY) && !defined(_WIN32)
# define QK__EALREADY (-EALREADY)
#else
# define QK__EALREADY (-4084)
#endif

#if defined(EBADF) && !defined(_WIN32)
# define QK__EBADF (-EBADF)
#else
# define QK__EBADF (-4083)
#endif

#if defined(EBUSY) && !defined(_WIN32)
# define QK__EBUSY (-EBUSY)
#else
# define QK__EBUSY (-4082)
#endif

#if defined(ECANCELED) && !defined(_WIN32)
# define QK__ECANCELED (-ECANCELED)
#else
# define QK__ECANCELED (-4081)
#endif

#if defined(ECHARSET) && !defined(_WIN32)
# define QK__ECHARSET (-ECHARSET)
#else
# define QK__ECHARSET (-4080)
#endif

#if defined(ECONNABORTED) && !defined(_WIN32)
# define QK__ECONNABORTED (-ECONNABORTED)
#else
# define QK__ECONNABORTED (-4079)
#endif

#if defined(ECONNREFUSED) && !defined(_WIN32)
# define QK__ECONNREFUSED (-ECONNREFUSED)
#else
# define QK__ECONNREFUSED (-4078)
#endif

#if defined(ECONNRESET) && !defined(_WIN32)
# define QK__ECONNRESET (-ECONNRESET)
#else
# define QK__ECONNRESET (-4077)
#endif

#if defined(EDESTADDRREQ) && !defined(_WIN32)
# define QK__EDESTADDRREQ (-EDESTADDRREQ)
#else
# define QK__EDESTADDRREQ (-4076)
#endif

#if defined(EEXIST) && !defined(_WIN32)
# define QK__EEXIST (-EEXIST)
#else
# define QK__EEXIST (-4075)
#endif

#if defined(EFAULT) && !defined(_WIN32)
# define QK__EFAULT (-EFAULT)
#else
# define QK__EFAULT (-4074)
#endif

#if defined(EHOSTUNREACH) && !defined(_WIN32)
# define QK__EHOSTUNREACH (-EHOSTUNREACH)
#else
# define QK__EHOSTUNREACH (-4073)
#endif

#if defined(EINTR) && !defined(_WIN32)
# define QK__EINTR (-EINTR)
#else
# define QK__EINTR (-4072)
#endif

#if defined(EINVAL) && !defined(_WIN32)
# define QK__EINVAL (-EINVAL)
#else
# define QK__EINVAL (-4071)
#endif

#if defined(EIO) && !defined(_WIN32)
# define QK__EIO (-EIO)
#else
# define QK__EIO (-4070)
#endif

#if defined(EISCONN) && !defined(_WIN32)
# define QK__EISCONN (-EISCONN)
#else
# define QK__EISCONN (-4069)
#endif

#if defined(EISDIR) && !defined(_WIN32)
# define QK__EISDIR (-EISDIR)
#else
# define QK__EISDIR (-4068)
#endif

#if defined(ELOOP) && !defined(_WIN32)
# define QK__ELOOP (-ELOOP)
#else
# define QK__ELOOP (-4067)
#endif

#if defined(EMFILE) && !defined(_WIN32)
# define QK__EMFILE (-EMFILE)
#else
# define QK__EMFILE (-4066)
#endif

#if defined(EMSGSIZE) && !defined(_WIN32)
# define QK__EMSGSIZE (-EMSGSIZE)
#else
# define QK__EMSGSIZE (-4065)
#endif

#if defined(ENAMETOOLONG) && !defined(_WIN32)
# define QK__ENAMETOOLONG (-ENAMETOOLONG)
#else
# define QK__ENAMETOOLONG (-4064)
#endif

#if defined(ENETDOWN) && !defined(_WIN32)
# define QK__ENETDOWN (-ENETDOWN)
#else
# define QK__ENETDOWN (-4063)
#endif

#if defined(ENETUNREACH) && !defined(_WIN32)
# define QK__ENETUNREACH (-ENETUNREACH)
#else
# define QK__ENETUNREACH (-4062)
#endif

#if defined(ENFILE) && !defined(_WIN32)
# define QK__ENFILE (-ENFILE)
#else
# define QK__ENFILE (-4061)
#endif

#if defined(ENOBUFS) && !defined(_WIN32)
# define QK__ENOBUFS (-ENOBUFS)
#else
# define QK__ENOBUFS (-4060)
#endif

#if defined(ENODEV) && !defined(_WIN32)
# define QK__ENODEV (-ENODEV)
#else
# define QK__ENODEV (-4059)
#endif

#if defined(ENOENT) && !defined(_WIN32)
# define QK__ENOENT (-ENOENT)
#else
# define QK__ENOENT (-4058)
#endif

#if defined(ENOMEM) && !defined(_WIN32)
# define QK__ENOMEM (-ENOMEM)
#else
# define QK__ENOMEM (-4057)
#endif

#if defined(ENONET) && !defined(_WIN32)
# define QK__ENONET (-ENONET)
#else
# define QK__ENONET (-4056)
#endif

#if defined(ENOSPC) && !defined(_WIN32)
# define QK__ENOSPC (-ENOSPC)
#else
# define QK__ENOSPC (-4055)
#endif

#if defined(ENOSYS) && !defined(_WIN32)
# define QK__ENOSYS (-ENOSYS)
#else
# define QK__ENOSYS (-4054)
#endif

#if defined(ENOTCONN) && !defined(_WIN32)
# define QK__ENOTCONN (-ENOTCONN)
#else
# define QK__ENOTCONN (-4053)
#endif

#if defined(ENOTDIR) && !defined(_WIN32)
# define QK__ENOTDIR (-ENOTDIR)
#else
# define QK__ENOTDIR (-4052)
#endif

#if defined(ENOTEMPTY) && !defined(_WIN32)
# define QK__ENOTEMPTY (-ENOTEMPTY)
#else
# define QK__ENOTEMPTY (-4051)
#endif

#if defined(ENOTSOCK) && !defined(_WIN32)
# define QK__ENOTSOCK (-ENOTSOCK)
#else
# define QK__ENOTSOCK (-4050)
#endif

#if defined(ENOTSUP) && !defined(_WIN32)
# define QK__ENOTSUP (-ENOTSUP)
#else
# define QK__ENOTSUP (-4049)
#endif

#if defined(EPERM) && !defined(_WIN32)
# define QK__EPERM (-EPERM)
#else
# define QK__EPERM (-4048)
#endif

#if defined(EPIPE) && !defined(_WIN32)
# define QK__EPIPE (-EPIPE)
#else
# define QK__EPIPE (-4047)
#endif

#if defined(EPROTO) && !defined(_WIN32)
# define QK__EPROTO (-EPROTO)
#else
# define QK__EPROTO (-4046)
#endif

#if defined(EPROTONOSUPPORT) && !defined(_WIN32)
# define QK__EPROTONOSUPPORT (-EPROTONOSUPPORT)
#else
# define QK__EPROTONOSUPPORT (-4045)
#endif

#if defined(EPROTOTYPE) && !defined(_WIN32)
# define QK__EPROTOTYPE (-EPROTOTYPE)
#else
# define QK__EPROTOTYPE (-4044)
#endif

#if defined(EROFS) && !defined(_WIN32)
# define QK__EROFS (-EROFS)
#else
# define QK__EROFS (-4043)
#endif

#if defined(ESHUTDOWN) && !defined(_WIN32)
# define QK__ESHUTDOWN (-ESHUTDOWN)
#else
# define QK__ESHUTDOWN (-4042)
#endif

#if defined(ESPIPE) && !defined(_WIN32)
# define QK__ESPIPE (-ESPIPE)
#else
# define QK__ESPIPE (-4041)
#endif

#if defined(ESRCH) && !defined(_WIN32)
# define QK__ESRCH (-ESRCH)
#else
# define QK__ESRCH (-4040)
#endif

#if defined(ETIMEDOUT) && !defined(_WIN32)
# define QK__ETIMEDOUT (-ETIMEDOUT)
#else
# define QK__ETIMEDOUT (-4039)
#endif

#if defined(ETXTBSY) && !defined(_WIN32)
# define QK__ETXTBSY (-ETXTBSY)
#else
# define QK__ETXTBSY (-4038)
#endif

#if defined(EXDEV) && !defined(_WIN32)
# define QK__EXDEV (-EXDEV)
#else
# define QK__EXDEV (-4037)
#endif

#if defined(EFBIG) && !defined(_WIN32)
# define QK__EFBIG (-EFBIG)
#else
# define QK__EFBIG (-4036)
#endif

#if defined(ENOPROTOOPT) && !defined(_WIN32)
# define QK__ENOPROTOOPT (-ENOPROTOOPT)
#else
# define QK__ENOPROTOOPT (-4035)
#endif

#if defined(ERANGE) && !defined(_WIN32)
# define QK__ERANGE (-ERANGE)
#else
# define QK__ERANGE (-4034)
#endif

#if defined(ENXIO) && !defined(_WIN32)
# define QK__ENXIO (-ENXIO)
#else
# define QK__ENXIO (-4033)
#endif

#if defined(EMLINK) && !defined(_WIN32)
# define QK__EMLINK (-EMLINK)
#else
# define QK__EMLINK (-4032)
#endif

#endif // QK_ERRNO_H
