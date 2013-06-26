#define ACE_NTRACE 0
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
#include <sstream>
#include <stdarg.h>
#include "log/logmsg.h"
#include "log/trace.h"
#pragma comment(lib, "framework.lib")
using namespace les;

void foo (void)
{
	LES_TRACE("foo")
}

void arg_test(char* i, ...)
{
#if defined(LES_NLOGGING)

	cout << "dddddddddddddddddddd" << endl;
#endif
	char* j=0;
	va_list arg_ptr;
	va_start(arg_ptr, i);

	j = va_arg(arg_ptr, char*);
	j = va_arg(arg_ptr, char*);

	//va_arg(arg_ptr, char*);
	//j = *(char*)arg_ptr;

	//va_arg(arg_ptr, char*);
	//j = *(char*)arg_ptr;

	//va_arg(arg_ptr, char*);
	//j = *(char*)arg_ptr;
}

class CA
{
public:
	CA() : _ms(0)
	{

	}
	~CA()
	{
	}

	void set(const char* m)
	{
		_ms = m;
	}

	const char* get() const
	{
		return _ms;
	}
protected:
private:
	const char* _ms;
};

int main(int argc, char *argv[])   
{
	arg_test("nihao", "zcz");
	ACE::init();
	WSADATA wsa; 
	WSAStartup(MAKEWORD(2,2),&wsa);

	CLogMsg::instance()->open(NULL, les::CLogMsg::STDOUT | les::CLogMsg::OFSTREAM);
	CLogMsg::instance()->makeDir("Server_log");
	CLogMsg::instance()->setLogName("fanren222.log");

	int i = 10;
	ACE_UNUSED_ARG(i);
	
	foo();
	//ACE_LOG_MSG->open(0, ACE_Log_Msg::OSTREAM | ACE_Log_Msg::STDERR);


	//ostream *output = new std::ofstream ("library.txt");
	//ACE_LOG_MSG->msg_ostream (output, 0);
	//////
	//ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("nihao")));
	//ACE_TRACE (ACE_TEXT ("main"));
	//foo();
	//cout << ::GetCurrentThreadId() << endl;
	//cout << ::getpid() << endl;
	//ACE_LOG_MSG->clr_flags (ACE_Log_Msg::OSTREAM);
	while (1)
	{
		LES_DEBUG("cjdklfkdsjflkdjdsjfjdkfjdkljfakljklfajsdklfjakljkjl" << endl << 145 << "sdj" << endl
			<< 5 +100000000 << endl)
		Sleep(800);
	}

 	return 0;
}