#include "log/logmsg.h"
#include <direct.h>
#include <process.h>

namespace les
{
	pid_t CLogMsg::_pid = -2;

	CLogMsg::CLogMsg(void) :
		_ostr(),
		_ofstream(NULL),
		_traceDepth(0),
		_traceActive(false),
		_traceEnabled(true),
		_dir(NULL),
		_file(NULL),
		_flags(CLogMsg::STDERR)
	{
		this->_ofstream = new ofstream();
	}

	CLogMsg::~CLogMsg(void)
	{
		if (NULL != this->_ofstream)
		{
			this->_ofstream->flush();
			delete this->_ofstream;
			this->_ofstream = NULL;
		}
	}

	ostringstream& CLogMsg::ostr(void)
	{
		return this->_ostr;
	}

	void CLogMsg::incTraceDepth(void)
	{
		this->_traceDepth++; 
	}

	void CLogMsg::decTraceDepth(void)
	{
		0 >= this->_traceDepth ? 0 : --this->_traceDepth;
	}

	int CLogMsg::getTraceDepth(void)
	{
		return this->_traceDepth;
	}

	void CLogMsg::setTraceDepth(int depth)
	{
		this->_traceDepth = depth;
	}

	bool CLogMsg::traceEnabled(void) const
	{
		return this->_traceEnabled;
	}

	void CLogMsg::startTrace(void)
	{
		this->_traceEnabled = true;
	}

	void CLogMsg::stopTrace(void)
	{
		this->_traceEnabled = false;
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

	void CLogMsg::setDir(const char* dir)
	{
		mkdir(dir);
		this->_dir = dir;
	}

	const char* CLogMsg::getFile(void) const
	{
		return this->_file;
	}

	void CLogMsg::setFile(const char* s)
	{
		this->_file = s;
	}

	void CLogMsg::clrFlags(u_long f)
	{
		LES_CLR_BITS(this->_flags, f);
	}

	void CLogMsg::setFlags(u_long f)
	{
		LES_SET_BITS(this->_flags, f);
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
			LES_CLR_BITS(this->_flags, CLogMsg::STDERR);
		}

		if (LES_BIT_ENABLED(flags, CLogMsg::OFSTREAM))
		{
			LES_SET_BITS(this->_flags, CLogMsg::OFSTREAM);
			if (NULL == this->_ofstream)
			{
				this->_ofstream = new ofstream();
			}
		}

		if (LES_BIT_ENABLED(flags, CLogMsg::SILENT))
		{
			LES_SET_BITS(this->_flags, CLogMsg::SILENT);
		}
	}

	void CLogMsg::log(const char* msg /* = NULL */)
	{
		if (NULL != msg)
		{
			this->_ostr.str(msg);
		}

		CLogRecord logRecord(this->getPID());
		logRecord.setMsgData(this->_ostr.str().c_str());
		this->_ostr.str("");
		this->log(logRecord);
	}

	void CLogMsg::log(CLogRecord& logRecord)
	{
		if (LES_BIT_DISABLED(this->_flags, CLogMsg::SILENT))
		{
			bool tracing = this->traceEnabled();
			this->stopTrace();
			
			if (LES_BIT_ENABLED(this->_flags, STDERR))
			{
				logRecord.print(stderr);
			}

			if (LES_BIT_ENABLED(this->_flags, OFSTREAM))
			{
				if (NULL != this->_ofstream)
				{
					string path;
					if (NULL != this->_dir)
					{
						path = string(this->_dir) + "/";
					}

					if (NULL == this->_file)
					{
						this->_file = "unkown.log";
					}
					path += this->_file;

					if (this->_ofstream->is_open())
					{
						this->_ofstream->close();
					}

					this->_ofstream->open(path.c_str(), std::ios::out | std::ios::app);
					if (!this->_ofstream->is_open())
					{
						return;
					}
					
					logRecord.print(*this->_ofstream);
				}
			}

			if (tracing)
			{
				this->startTrace();
			}
		}
	}

	CLogMsg* CLogMsg::instance(void)
	{
		static CLogMsg instance;
		return &instance;
	}
}