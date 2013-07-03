#ifndef _LES_INET_ADDR_H_
#define _LES_INET_ADDR_H_

#include "socket/addr.h"

namespace les
{
	class CInetAddr : public CAddr
	{
	public:
		CInetAddr(void);
		CInetAddr(const CInetAddr& ref);
		CInetAddr(const sockaddr_in* saddr, int len);
		CInetAddr(u_short port, const char hostName[], int af = AF_UNSPEC);
		CInetAddr(u_short port, u_long ipAddr);
		CInetAddr(const char portName, const char hostName, const char protocol[] = "tcp");
		CInetAddr(const char portName, u_long ipAddr, const char protocol[] = "tcp");
		~CInetAddr(void);
		
		int set(const CInetAddr& ref);
		int set(const sockaddr_in* saddr, int len);
		int set(u_short port, const char hostName[], bool encode = true, int af = AF_UNSPEC);
		int set(u_short port, u_long ipAddr, bool encode = true, bool map = false);
		int set(const char portName[], const char hostName[], const char protocol[] = "tcp");
		int set(const char portName[], u_long ipAddr, const char protocol[] = "tcp");

		void setPort(u_short port, bool encode);
		u_short getPort(void) const;

		virtual void setAddr(void*, int);
		virtual void* getAddr(void) const;
		
		int setAddress(const char* ipAddr, int len, bool encode = true, bool map = false);
	private:
		int getPortFromPortName(const char portName[], const char protocol[]);
		void reset(void);

		union
		{
			sockaddr_in _in4;
#ifdef HAS_IPV6
			sockaddr_in6 _in6;
#endif
		} _inetAddr;
	};
}

#endif