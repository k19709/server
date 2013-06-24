#ifndef _LES_SOCKET_HELPER_H_
#define _LES_SOCKET_HELPER_H_

#include "common.h"
#include "config.h"

namespace les
{	
	bool startupWSA(void);
	
	bool ipv4Enabled(int type, int protocol);
	bool ipv6Enabled(int type, int protocol);
}
#endif