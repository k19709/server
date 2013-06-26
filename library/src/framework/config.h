#ifndef _LES_CONFIG_H_
#define _LES_CONFIG_H_

#if !defined(INT_VERSION)
#define INT_VERSION 10001
#endif

#if !defined(STRING_VERSION)
#define STRING_VERSION "1.0.1"
#endif

#if !defined(MAXLOGMSGLEN)
#define MAXLOGMSGLEN 4*1024
#endif

#define AF_ANY  -1
#define HAS_IPV6

#define LES_NLOGGING 0
#define LES_NDEBUG 0
#define LES_NTRACE 0

#endif