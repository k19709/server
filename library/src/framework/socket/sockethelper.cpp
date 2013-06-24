#include "socket/sockethelper.h"

namespace les
{
	bool startupWSA(void)
	{
		WSADATA wsa; 
		if (0 != WSAStartup(MAKEWORD(2,1),&wsa))
		{
			return false;
		}
		return true;
	}

	bool ipv4Enabled(int type, int protocol)
	{
		SOCKET s = socket(AF_INET, type, protocol);
		if (INVALID_SOCKET != s)
		{
			closesocket(s);
			return true;
		}
		return false;
	}

	bool ipv6Enabled(int type, int protocol)
	{
		SOCKET s = socket(AF_INET6, type, protocol);
		if (INVALID_SOCKET != s)
		{
			closesocket(s);
			return true;
		}
		return false;
	}
}