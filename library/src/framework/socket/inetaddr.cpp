#include "socket/inetaddr.h"
#include "socket/sockethelper.h"
#include "log/logmsg.h"
#include "util/error.h"

namespace les
{
	CInetAddr::CInetAddr(void) : CAddr()
	{
		this->reset();
	}

	CInetAddr::CInetAddr(const CInetAddr& ref) : CAddr()
	{
		this->reset();
		this->set(ref);
	}

	CInetAddr::CInetAddr(const sockaddr_in* saddr, int len) : CAddr()
	{
		this->reset();
		if (0 != this->set(saddr, len))
		{
			LES_ERROR("CInetAddr::CInetAddr() error")
		}
	}

	CInetAddr::CInetAddr(u_short port, const char hostName[], int af /* = AF_UNSPEC */) : CAddr()
	{
		// the @a port is assumed to be in host byte order 
		this->reset();
		if (0 != this->set(port, hostName, true, af))
		{
			//LES_ERROR("CInetAddr::CInetAddr() error: " << getLastError() )
		}
	}

	CInetAddr::CInetAddr(u_short port, u_long ipAddr) : CAddr()
	{
		// the @a port and @a ipAddr are assumed to be in host byte order
		this->reset();
		if (0 != this->set(port, ipAddr))
		{
			LES_ERROR("CInetAddr::CInetAddr() error")
		}
	}

	CInetAddr::CInetAddr(const char portName, const char hostName, const char protocol[] /* = "tcp" */) : CAddr()
	{
		// if the @a protocol is tcp6, af select AF_INET6, otherwise af select AF_UNSPEC
		this->reset();
		if (0 != this->set(portName, hostName, protocol))
		{
			LES_ERROR("CInetAddr::CInetAddr() error: " << getLastError() )
		}
	}

	CInetAddr::CInetAddr(const char portName, u_long ipAddr, const char protocol[] /* = "tcp" */) : CAddr()
	{
		// the @a ipAddr is assumed to be in host byte order
		this->reset();
		if (0 != this->set(portName, htonl(ipAddr), protocol))
		{
			LES_ERROR("CInetAddr::CInetAddr() error: " << getLastError() )
		}
	}

	CInetAddr::~CInetAddr(void)
	{
	}

	int CInetAddr::set(const CInetAddr& ref)
	{
		this->setType(ref.getType());
		this->setSize(ref.getSize());
		
		if (AF_ANY != ref.getType())
		{
			memcpy(&this->_inetAddr, &ref._inetAddr, ref.getSize());
		}

		return 0;
	}

	int CInetAddr::set(const sockaddr_in* saddr, int len)
	{
		if (AF_INET == saddr->sin_family)
		{
			int maxLen = (int)sizeof(this->_inetAddr._in4);
			if (len > maxLen)
			{
				len = maxLen;
			}

			memcpy(&this->_inetAddr._in4, saddr, len);
			this->baseSet(AF_INET, len);
			return 0;
		}
#ifdef HAS_IPV6
		else if (AF_INET6 == saddr->sin_family)
		{
			int maxlen = (int)sizeof(this->_inetAddr._in6);
			if (len > maxlen)
			{
				len = maxlen;
			}

			memcpy(&this->_inetAddr._in6, saddr, len);
			this->baseSet(AF_INET6, len);
			return 0;
		}
#endif

		return -1;
	}

	int CInetAddr::set(u_short port, const char hostName[], bool encode /* = true */, int af /* = AF_UNSPEC */)
	{
		if (hostName == 0)
		{
			// invalid hostName
			LES_ERROR("CInetAddr::set() error: invalid hostName")
			return -1;
		}

		struct addrinfo hints;
		struct addrinfo* result = NULL;
		memset(&hints, 0, sizeof(hints));
		memset(&this->_inetAddr, 0, sizeof(this->_inetAddr));

#ifdef HAS_IPV6
		if (AF_UNSPEC == af || AF_INET6 == af)
		{
			hints.ai_family = AF_INET6;
			int error = getaddrinfo(hostName, 0, &hints, &result);
			if (0 != error)
			{
				// error
				if (AF_INET6 == af)
				{
					if (NULL != result)
					{
						freeaddrinfo(result);	
					}
					return -1;
				}
				af = AF_INET;
			}
		}

		if (AF_INET == af)
		{
			hints.ai_family = AF_INET;
			int error = getaddrinfo(hostName, 0, &hints, &result);
			if (0 != error)
			{
				// error
				if (NULL != result)
				{
					freeaddrinfo(result);	
				}
				return -1;
			}
		}

		if (NULL != result)
		{
			if (AF_INET == result->ai_family)
			{
				this->baseSet(AF_INET, sizeof(this->_inetAddr._in4));
				struct sockaddr_in* sin = (struct sockaddr_in*)(result->ai_addr);
				this->setAddr(&sin->sin_addr, sizeof(sin->sin_addr));
			}
			else if (AF_INET6 == result->ai_family)
			{
				this->baseSet(AF_INET6, sizeof(this->_inetAddr._in6));
				struct sockaddr_in6* sin6 = (struct sockaddr_in6*)(result->ai_addr);
				this->setAddr(&sin6->sin6_addr, sizeof(sin6->sin6_addr));
				this->_inetAddr._in6.sin6_scope_id = sin6->sin6_scope_id;
			}
			this->setPort(port, encode);
			freeaddrinfo(result);
			return 0;
		}
#endif
		if (AF_INET == af)
		{
			hints.ai_family = AF_INET;
			int error = getaddrinfo(hostName, 0, &hints, &result);
			if (0 != error)
			{
				// error
				if (NULL != result)
				{
					freeaddrinfo(result);	
				}
				return -1;
			}
		}

		if (NULL != result)
		{
			this->baseSet(AF_INET, sizeof(this->_inetAddr._in4));
			struct sockaddr_in* sin = (struct sockaddr_in*)(result->ai_addr);
			this->setAddr(&sin->sin_addr, sizeof(sin->sin_addr));
			this->setPort(port, encode);
			freeaddrinfo(result);
			return 0;
		}

		return -1;
	}

	int CInetAddr::set(u_short port, u_long ipAddr, bool encode /* = true */, bool map /* = false */)
	{
		int reslut = this->setAddress(reinterpret_cast<const char*>(&ipAddr), sizeof(ipAddr), encode, map);
		this->setPort(port, encode);
		return reslut;
	}

	int CInetAddr::set(const char portName[], const char hostName[], const char protocol[] /* = "tcp" */)
	{
		int port = this->getPortFromPortName(portName, protocol);
		if (-1 == port)
		{
			return -1;
		}
		
		int af = AF_UNSPEC;
#ifdef HAS_IPV6
		if (0 == strcmp(protocol, "tcp6"))
		{
			af = AF_INET6;
		}
#endif
		return this->set((u_short)(port), hostName, false, af);
	}

	int CInetAddr::set(const char portName[], u_long ipAddr, const char protocol[] /* = "tcp" */)
	{
		int port = this->getPortFromPortName(portName, protocol);
		if (-1 == port)
		{
			return -1;
		}

		return this->set((u_short)(port), ipAddr, false);
	}

	void CInetAddr::setPort(u_short port, bool encode)
	{
		if (encode)
		{
			port = htons(port);
		}

#ifdef HAS_IPV6
		if (AF_INET6 == this->getType())
		{
			_inetAddr._in6.sin6_port = port;
		}
		else
#endif
		_inetAddr._in4.sin_port = port;
	}

	u_short CInetAddr::getPort(void) const
	{
#ifdef HAS_IPV6
		if (AF_INET6 == this->getType())
		{
			return _inetAddr._in6.sin6_port;
		}
		else
#endif
			return _inetAddr._in4.sin_port;
	}

	void CInetAddr::setAddr(void* addr, int len)
	{
		this->setAddress(reinterpret_cast<const char*>(addr), len, false, false);
	}

	void* CInetAddr::getAddr(void) const
	{
		return (void*)&this->_inetAddr;
	}

	int CInetAddr::setAddress(const char* ipAddr, int len, bool encode /* = true */, bool map /* = false */)
	{
		if (4 != len && 16 != len)
		{
			// input error
			LES_ERROR("CInetAddr::setAddress() input error: len = " << len)
			return -1;
		}
		if (4 != len && encode)
		{
			// input error
			LES_ERROR("CInetAddr::setAddress() input error: len = " << len << " encode is true")
			return -1;
		}

		if (4 == len)
		{
			u_long ip4 = *reinterpret_cast<const u_long *> (ipAddr);
			if (encode)
			{
				ip4 = htonl(ip4);
			}

			if ((AF_INET == this->getType() && !map) || !map)
			{
				this->baseSet(AF_INET, sizeof(this->_inetAddr._in4));
				this->_inetAddr._in4.sin_family = AF_INET;
				memcpy(&this->_inetAddr._in4.sin_addr, &ip4, len);
			}
#ifdef HAS_IPV6
			else
			{
				this->baseSet(AF_INET6, sizeof(this->_inetAddr._in6));
				this->_inetAddr._in6.sin6_family = AF_INET6;
				if (ip4 == htonl(INADDR_ANY))
				{
					// if the addr is 0.0.0.0
					in6_addr const ip6 = in6addr_any;
					memcpy (&this->_inetAddr._in6.sin6_addr, &ip6, sizeof (ip6));
					return 0;
				}

				// an IPv4-mapped IPv6 address is defined as 0:0:0:0:0:ffff:IPv4_address.
				memset(&this->_inetAddr._in6.sin6_addr, 0, 16);
				this->_inetAddr._in6.sin6_addr.s6_addr[10] =
					this->_inetAddr._in6.sin6_addr.s6_addr[11] = 0xff;
				memcpy(&this->_inetAddr._in6.sin6_addr.s6_addr[12], &ip4, 4);
			}
#endif
		}
#ifdef HAS_IPV6
		else if (16 == len)
		{
			if (AF_INET6 != this->getType())
			{
				// input error
				LES_ERROR("CInetAddr::setAddress() inout error: type = " << this->getType())
				return -1;
			}

			this->baseSet(AF_INET6, sizeof(this->_inetAddr._in6));
			this->_inetAddr._in6.sin6_family = AF_INET6;
			memcpy(&this->_inetAddr._in6.sin6_addr, &ipAddr, len);
			return 0;
		}
		return -1;
#endif
	}

	int CInetAddr::getPortFromPortName(const char portName[], const char protocol[])
	{
		struct servent *p = NULL;
		p = getservbyname(portName, protocol);
		if (NULL != p)
		{
			// return the port which is network by order 
			return p->s_port;
		}

		return -1;
	}

	void CInetAddr::reset(void)
	{
		memset(&this->_inetAddr, 0, sizeof(this->_inetAddr));
		if (AF_INET == this->getType())
		{
			this->_inetAddr._in4.sin_family = AF_INET;
		}
#ifdef HAS_IPV6
		else if (AF_INET6 == this->getType())
		{
			this->_inetAddr._in6.sin6_family = AF_INET6;
		}
#endif
	}

}