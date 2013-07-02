#include "log/logmsg.h"
#include <direct.h>
#include <process.h>

namespace les
{
	u_long CLogMsg::_flags = CLogMsg::STDERR;
	pid_t CLogMsg::_pid = -2;

	CLogMsg::CLogMsg(void) :
		_ostr(),
		_os(),
		_traceDepth(0),
		_traceActive(false),
		_tracingEnabled(true),
		_dir(NULL),
		_logName(NULL)
	{
	}

	CLogMsg::~CLogMsg(void)
	{
		_os.flush();
	}

	CLogMsg* CLogMsg::instance(void)
	{
		static CLogMsg instance;
		return &instance;
	}

	bool CLogMsg::tracingEnabled(void) const
	{
		return this->_tracingEnabled;
	}

	void CLogMsg::startTracing(void)
	{
		this->_tracingEnabled = true;
	}

	void CLogMsg::stopTracing(void)
	{
		this->_tracingEnabled = false;
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

	pid_t CLogMsg::getPID(void)
	{
		if (-2 == CLogMsg::_pid)
		{
			CLogMsg::_pid = ::getpid();
		}
		return CLogMsg::_pid;
	}

	void CLogMsg::open(u_long flags)
	{
		if (!LES_BIT_ENABLED(flags, CLogMsg::STDERR))
		{
			LES_CLR_BITS(CLogMsg::_flags, CLogMsg::STDERR);
		}

		if (LES_BIT_ENABLED(flags, CLogMsg::OSTREAM))
		{
			LES_SET_BITS(CLogMsg::_flags, CLogMsg::OSTREAM);
			this->_os = cerr;
		}

		if (LES_BIT_ENABLED(flags, CLogMsg::SILENT))
		{
			LES_SET_BITS(CLogMsg::_flags, CLogMsg::SILENT);
		}
	}

	void CLogMsg::log(const char* msg /* = NULL */)
	{
		if (NULL != msg)
		{
			this->setStr(msg);
		}

		CLogRecord logRecord(this->getPID());
		logRecord.msgData(this->_ostr.str().c_str());
		this->_ostr.str("");
		this->log(logRecord);
	}

	void CLogMsg::log(CLogRecord& logRecord)
	{
		if (LES_BIT_DISABLED(CLogMsg::_flags, CLogMsg::SILENT))
		{
			bool tracing = this->tracingEnabled();
			this->stopTracing();
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

			if (tracing)
			{
				this->startTracing();
			}
		}
	}
}