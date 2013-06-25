#include "log/logmsg.h"
#include <direct.h>
#include <process.h>

namespace les
{
	const char* CLogMsg::_progName = NULL;
	u_long CLogMsg::_flags = 0;

	CLogMsg::CLogMsg(void) :
		_traceEnabled(true),
		_traceActive(false),
		_dir(NULL),
		_logName(NULL),
		_ostr(),
		_ofs()
	{
		_ofs.flush();
	}

	CLogMsg::~CLogMsg(void)
	{
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
		mkdir(dir);
		this->_dir = dir;
	}

	const char* CLogMsg::getLogName(void) const
	{
		return this->_logName;
	}

	void CLogMsg::setLogName(const char* name)
	{
		this->_logName = name;
	}

	ostringstream& CLogMsg::getStr(void)
	{
		return this->_ostr;
	}

	void CLogMsg::setStr(const char* str)
	{
		this->_ostr.str("");
		this->_ostr << str;
	}

	void CLogMsg::clrFlags(u_long f)
	{
		LES_CLR_BITS(CLogMsg::_flags, f);
	}

	void CLogMsg::setFlags(u_long f)
	{
		LES_SET_BITS(CLogMsg::_flags, f);
	}

	u_int CLogMsg::getPID(void)
	{
		return ::getpid();
	}

	u_int CLogMsg::getThreadId(void)
	{
		return ::GetCurrentThreadId();
	}

	void CLogMsg::open(const char* progName, u_long flags)
	{
		if (NULL != progName)
		{
			CLogMsg::_progName = progName;
		}
		else if (NULL == progName)
		{
			CLogMsg::_progName = "<unknown>";
		}

		if (LES_BIT_ENABLED(flags, STDOUT))
		{
			LES_SET_BITS(CLogMsg::_flags, STDOUT);
		}

		if (LES_BIT_ENABLED(flags, OFSTREAM))
		{
			LES_SET_BITS(CLogMsg::_flags, OFSTREAM);
		}
	}

	void CLogMsg::log(void)
	{
		CLogRecord logRecord(this->getPID(), this->getThreadId());
		logRecord.setData(this->_ostr.str().c_str());
		this->_ostr.str("");
		this->log(logRecord);
	}

	void CLogMsg::log(const char* msg)
	{
		this->setStr(msg);
		this->log();
	}

	void CLogMsg::log(CLogRecord& logRecord)
	{
		if (LES_BIT_ENABLED(CLogMsg::_flags, STDOUT))
		{
			logRecord.print(stdout);
		}

		if (LES_BIT_ENABLED(CLogMsg::_flags, OFSTREAM))
		{
			static int count = 0;
			string s = string(this->_dir) + "/";
			s += this->_logName;
			if (this->_ofs.is_open())
			{
				this->_ofs.close();
			}

			this->_ofs.open(s.c_str(), std::ios::out | std::ios::app);
			if (!this->_ofs.is_open())
			{
				return;
			}
			logRecord.print(this->_ofs);

			if (++count % 2 == 0)
			{
				this->_ofs.flush();
				count = 0;
			}
		}
	}
}