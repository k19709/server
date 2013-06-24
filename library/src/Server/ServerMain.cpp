#define ACE_NTRACE 0
#include "framework/link.h"
#include "framework/common.h"
#include "framework/json/json.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_stdlib.h"
#include "ace/Global_Macros.h"
#include "ace/INET_Addr.h"
#include "ace/Log_Msg.h"
#include "ace/Init_ACE.h"
#include "ace/streams.h"
#include "framework/socket/addr.h"
#include <direct.h>
#include <sstream>
#include <stdarg.h>

void foo (void)
{
	ACE_TRACE (ACE_TEXT ("foo"));
	ACE_DEBUG ((LM_INFO, ACE_TEXT ("%IHowdy Pardner\n")));
}

void arg_test(int i, ...)
{
	int j=0;
	va_list arg_ptr;
	va_start(arg_ptr, i);
	j = *(int*)arg_ptr;

	va_arg(arg_ptr, int);
	j = *(int*)arg_ptr;

	va_arg(arg_ptr, int);
	j = *(int*)arg_ptr;

	va_arg(arg_ptr, int);
	j = *(int*)arg_ptr;

	va_arg(arg_ptr, int);
	j = *(int*)arg_ptr;
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
	char des[] = "Hello,i am!";
	char source[] = "abc\0def";
	strncpy(des,source,5);

	arg_test(400000,1,2,3,10);

	stringstream k;
	//k << "jdjjd" << "sdjdjfjfjkjdlkjfkladjlkjdlkjfakl" << endl;
	string sss = "10a00aa";
	k << sss;
	int i;
	k >> i;
	cout << i;
	ACE::init();
	WSADATA wsa; 
	WSAStartup(MAKEWORD(2,2),&wsa);


	ACE_LOG_MSG->open(0, ACE_Log_Msg::OSTREAM | ACE_Log_Msg::STDERR);


	ostream *output = new std::ofstream ("library.txt");
	ACE_LOG_MSG->msg_ostream (output, 0);
	
	ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("nihao")));
	ACE_TRACE (ACE_TEXT ("main"));
	foo();
	//cout << ::GetCurrentThreadId() << endl;
	//cout << ::getpid() << endl;
	//ACE_LOG_MSG->clr_flags (ACE_Log_Msg::OSTREAM);
	//while (1)
	//{
	//	;
	//}
 	return 0;
}