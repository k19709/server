#include "socket/socket.h"

namespace les
{
	CSocket::CSocket(void)
	{
	}

	CSocket::CSocket(int af, int type, int protocol, int reUseAddr)
	{
		if (-1 == this->open(af, type, protocol, reUseAddr))
		{
		}
	}

	CSocket::CSocket(int af, int type, int protocol, LPWSAPROTOCOL_INFO info, GROUP g, DWORD flags, int reUseAddr)
	{
		if (-1 == this->open(af, type, protocol, info, g, flags, reUseAddr))
		{
		}
	}

	CSocket::~CSocket(void)
	{
	}

	int CSocket::setOpt(int level, int optName, void* optVal, int optLen)
	{
		// if successful, then return 0, otherwise return -1
		if (SOCKET_ERROR == setsockopt(this->get(), level, optName, (const char*)optVal, optLen ))
		{
			return -1;
		}

		return 0;
	}

	int CSocket::getOpt(int level, int optName, void* optVal, int* optLen)
	{
		// if successful, then return 0, otherwise return -1
		if (SOCKET_ERROR == getsockopt(this->get(), level, optName, (char*)optVal, optLen))
		{
			return -1;
		}

		return 0;
	}

	int CSocket::open(int af, int type, int protocol, int reUseAddr)
	{
		// reuse addr
		int optVal = 1;
		this->set(socket(af, type, protocol));
		
		if (INVALID_SOCKET == this->get())
		{
			return -1;
		}
		else if (af != AF_UNIX 
				 && reUseAddr
				 && this->setOpt(SOL_SOCKET, 
								 SO_REUSEADDR,
								 &optVal,
								 sizeof(optVal)) == -1 )
		{
			this->close();
			return -1;
		}

		return 0;
	}

	int CSocket::open(int af, int type, int protocol, LPWSAPROTOCOL_INFO info, GROUP g, DWORD flags, int reUseAddr)
	{
		int optVal = 1;
		this->set(WSASocket(af, type, protocol, info, g, flags));

		if (INVALID_SOCKET == this->get())
		{
			return -1;
		}
		else if (reUseAddr
				 && this->setOpt(SOL_SOCKET,
								 SO_REUSEADDR,
								 &optVal,
								 sizeof(optVal)) == -1)
		{
			this->close();
			return -1;
		}

		return 0;
	}

	int CSocket::close(void)
	{
		// if successful, then return 0, otherwise return -1
		int result = 0;
		if ( INVALID_SOCKET != get())
		{
			result = closesocket(this->get());
			this->set(INVALID_SOCKET);
		}

		return result;
	}

	int CSocket::getRomoteAddr(CAddr& addr) const
	{
		struct sockaddr sa;
		int len = sizeof(sa);

		if (SOCKET_ERROR == getpeername(this->get(), &sa, &len))
		{
			return -1;
		}
		
		addr.setType(sa.sa_family);
		addr.setSize(len);
		return 0;
	}

	int CSocket::getLocalAddr(CAddr& addr) const
	{
		struct sockaddr sa;
		int len = sizeof(sa);

		if (SOCKET_ERROR == getsockname(this->get(), &sa, &len))
		{
			return -1;
		}

		addr.setType(sa.sa_family);
		addr.setSize(len);
		return 0;
	}

	void CSocket::set(SOCKET s)
	{
		this->_socket = s;
	}

	SOCKET CSocket::get(void) const
	{
		return this->_socket;
	}
}