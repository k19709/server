#ifndef _LES_SOCKET_H_
#define _LES_SOCKET_H_

#include "common.h"
#include "link.h"
#include "socket/addr.h"

namespace les
{
	class CSocket
	{
	public:
		int setOpt(int level, int optName, void* optVal, int optLen);
		int getOpt(int level, int optName, void* optVal, int* optLen);
		
		int open(int af, int type, int protocol, int reUseAddr);
		int open(int af, int type, int protocol, LPWSAPROTOCOL_INFO info, GROUP g, DWORD flags, int reUseAddr);
		int close(void);

		int getRomoteAddr(CAddr& addr) const;
		int getLocalAddr(CAddr& addr) const;

		void set(SOCKET s);
		SOCKET get(void)const;

	private:
		CSocket(void);
		CSocket(int af, int type, int protocol, int reUseAddr);
		CSocket(int af, int type, int protocol, LPWSAPROTOCOL_INFO info, GROUP g, DWORD flags, int reUseAddr);
		~CSocket(void);

	private:
		SOCKET _socket;
	};
}

#endif