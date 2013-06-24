#include "log/logmsg.h"

namespace les
{
	CLogMsg::CLogMsg(void) :
		_traceEnabled(true),
		_traceActive(false),
		_dir(NULL),
		_fileName(NULL),
		_msg(NULL)
	{
		_msg = new char[MAXPATHLEN + 1];
	}

	CLogMsg::~CLogMsg(void)
	{
		if (NULL != this->_msg)
		{
			delete[] this->_msg;
		}
	}

	CLogMsg* CLogMsg::instance(void)
	{
		static CLogMsg ins;
		return &ins;
	}

	bool CLogMsg::traceEnabled(void) const
	{
		return this->_traceEnabled;
	}

	void CLogMsg::traceEnabled(bool enabled)
	{
		this->_traceEnabled = enabled;
	}

	bool CLogMsg::traceActive(void) const
	{
		return this->_traceActive;
	}

	void CLogMsg::traceActive(bool active)
	{
		this->_traceActive = active;
	}

	const char* CLogMsg::getDir(void) const
	{
		return this->_dir;
	}

	void CLogMsg::makeDir(const char* dir)
	{
		this->_dir = dir;
	}

	const char* CLogMsg::getFileName(void) const
	{
		return this->_fileName;
	}

	void CLogMsg::setFileName(const char* file)
	{
		this->_fileName = file;
	}

	ostream* CLogMsg::getMsgOstream(void) const
	{
		return this->_msgOstream;
	}

	void CLogMsg::setMsgOstream(ostream* os)
	{
		this->_msgOstream = os;
	}

	char* CLogMsg::getMsg(void) const
	{
		return this->_msg;
	}



	int CLogMsg::open(const char* programName, u_long flags)
	{
		if (NULL != programName)
		{
			CLogMsg::_programName = programName;
		}
		else if (NULL == programName)
		{
			CLogMsg::_programName = "<unknown>";
		}

		if (LES_BIT_ENABLED(flags, STDERR))
		{
			LES_SET_BITS(CLogMsg::_flags, STDERR);
		}

		if (LES_BIT_ENABLED(flags, STREAM))
		{
			LES_SET_BITS(CLogMsg::_flags, STREAM);
			this->setMsgOstream(&std::cerr);
		}

		return 0;
	}




}