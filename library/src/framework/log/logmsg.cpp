#include "log/logmsg.h"
#include <direct.h>
#include <process.h>

namespace les
{
	u_long CLogMsg::_flags = 0;

	CLogMsg::CLogMsg(void) :
		_traceEnabled(true),
		_traceActive(false),
		_dir(NULL),
		_logName(NULL),
		_ostr(),
		_os()
	{
		_os.flush();
	}

	CLogMsg::~CLogMsg(void)
	{
	}

	CLogMsg* CLogMsg::instance(void)
	{
		static CLogMsg instance;
		return &instance;
	}

	bool CLogMsg::tracingEnabled(void) const
	{
		return this->_traceEnabled;
	}

	void CLogMsg::tracingEnabled(bool enabled)
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

	void CLogMsg::open(u_long flags)
	{
		if (LES_BIT_ENABLED(flags, STDERR))
		{
			LES_SET_BITS(CLogMsg::_flags, STDERR);
		}

		if (LES_BIT_ENABLED(flags, OSTREAM))
		{
			LES_SET_BITS(CLogMsg::_flags, OSTREAM);
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
		if (LES_BIT_ENABLED(CLogMsg::_flags, STDERR))
		{
			logRecord.print(stdout);
		}

		if (LES_BIT_ENABLED(CLogMsg::_flags, OSTREAM))
		{
			string path;
			if (NULL != this->_dir)
			{
				path = string(this->_dir) + "/";
			}

			if (NULL == this->_logName)
			{
				this->_logName = "unknown.log";
			}
			path += this->_logName;

			if (this->_os.is_open())
			{
				this->_os.close();
			}

			this->_os.open(path.c_str(), std::ios::out | std::ios::app);
			if (!this->_os.is_open())
			{
				return;
			}
			logRecord.print(this->_os);
		}
	}
}