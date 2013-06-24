#include "log/logmsg.h"

namespace les
{
	CLogMsg::CLogMsg(void) :
		_traceEnbled(true),
		_traceActive(false),
		_dir(0),
		_fileName(0),
		_msg(NULL)
	{
		_msg = new char[MAXPATHLEN + 1];
	}

	CLogMsg::~CLogMsg(void)
	{
		if (NULL != _msg)
		{
			delete[] _msg;
		}

		if (NULL != _programName)
		{
			free((void*)_programName);
			_programName = NULL;
		}
		
	}
}