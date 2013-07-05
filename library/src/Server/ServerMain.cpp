#include "link.h"
#include "common.h"
#include "json/json.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_stdlib.h"
#include "ace/Global_Macros.h"
#include "ace/INET_Addr.h"
#include "ace/Log_Msg.h"
#include "ace/Init_ACE.h"
#include "ace/streams.h"
#include "socket/addr.h"
#include <direct.h>
#include <stdarg.h>
#include "log/trace.h"
#pragma comment(lib, "framework.lib")
using namespace les;

int foo (void)
{
	LES_TRACE("foo")
	return 0;
}

int main(int argc, char *argv[])   
{
	ACE::init();
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	CLogMsg::instance()->open(les::CLogMsg::STDERR | les::CLogMsg::OFSTREAM);
	CLogMsg::instance()->setDir("Server_log");
	CLogMsg::instance()->setFile("fanren2.log");

	int i = 10;
	ACE_UNUSED_ARG(i);
	
	foo();
	while (1)
	{
		LES_DEBUG("cjdklfkdsjflkdjdsjfjdkfjdkljfakljklfajsdklfjakljkjl" << foo())
		Sleep(800);
	}

 	return 0;
}