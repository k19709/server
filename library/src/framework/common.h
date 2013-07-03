#ifndef _LES_COMMON_H_
#define _LES_COMMON_H_

#include <string>
#include <map>
#include <vector>
#include <list>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

#include "config.h"

typedef unsigned short u_short;
typedef unsigned long u_long;
typedef int pid_t;

#define LES_BIT_ENABLED(WORD, BIT) (((WORD) & (BIT)) != 0)
#define LES_BIT_DISABLED(WORD, BIT) (((WORD) & (BIT)) == 0)
#define LES_BIT_CMP_MASK(WORD, BIT, MASK) (((WORD) & (BIT)) == MASK)
#define LES_SET_BITS(WORD, BITS) (WORD |= (BITS))
#define LES_CLR_BITS(WORD, BITS) (WORD &= ~(BITS))

#endif