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

const std::string JSON_KEY_MOUNT_STARS_LEVEL = "m_stLv";				//坐骑星辰等级
const std::string JSON_KEY_MOUNT_STARS_TARGET = "m_stTa";				//坐骑星辰目标
const std::string JSON_KEY_MOUNT_STARS_LAST_COLOR = "m_stLc";			//坐骑上一次炼神出的星体
const std::string JSON_KEY_MOUNT_STARS_HAVE = "m_haSt";					//是否拥有星辰

int main(int argc, char *argv[])   
{
	ACE::init();
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	Json::Value mountJson;
	mountJson[JSON_KEY_MOUNT_STARS_LEVEL].clear();
	mountJson[JSON_KEY_MOUNT_STARS_TARGET].clear();
	mountJson[JSON_KEY_MOUNT_STARS_LAST_COLOR].clear();

	Json::Value tmpJson;
	tmpJson.append( NULL );
	tmpJson.clear();
	int i = 0;
	mountJson[JSON_KEY_MOUNT_STARS_LEVEL][i] = Json::Value( tmpJson );
	mountJson[JSON_KEY_MOUNT_STARS_TARGET][i] = Json::Value( 0 );
	mountJson[JSON_KEY_MOUNT_STARS_LAST_COLOR][i] = Json::Value( "0#0" );
	mountJson[JSON_KEY_MOUNT_STARS_HAVE] = Json::Value( 1 );

	std::string s = mountJson.toStyledString();

 	return 0;
}