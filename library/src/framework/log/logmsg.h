#ifndef _LES_LOG_MSG_H_
#define _LES_LOG_MSG_H_

#include "config.h"
#include "common.h"
#include "log/logrecord.h"

namespace les
{
#if !defined(NEED_LOG)
#if !defined(LES_DEBUG)
#define LES_DEBUG(X) \
	do \
	{ \
	}while (0);
#endif
#else
#if !defined(LES_DEBUG)
#define LES_DEBUG(X) \
	do \
	{\
	CLogMsg* ____ = CLogMsg::instance();\
	____->getStr() << X;\
	____->log();\
	} while (0);
#endif
#endif

#define LES_LOG_MSG CLogMsg::instance()

	class CLogMsg
	{
	public:
		// log flags
		enum
		{
			STDOUT		= 1,	//write msg to stdout
			OFSTREAM	= 2,	//write msg to ofstream
		};

		static CLogMsg* instance(void);

		bool traceEnabled(void) const;
		void traceEnabled(bool enabled);

		bool traceActive(void) const;
		void traceActive(bool active);
		
		const char* getDir(void) const;
		void makeDir(const char* dir);

		const char* getLogName(void) const;
		void setLogName(const char* name);

		ostringstream& getStr(void);
		void setStr(const char* str);

		void clrFlags(u_long f);
		void setFlags(u_long f);

		u_int getPID(void);
		u_int getThreadId(void);

		void open(const char* progName, u_long flags);
		void log(void);
		void log(const char* msg);
		void log(CLogRecord& logRecord);

	private:
		CLogMsg(void);
		~CLogMsg(void);

	private:
		bool _traceEnabled;
		bool _traceActive;
		
		const char* _dir;
		const char* _logName;
		
		ostringstream _ostr;
		ofstream _ofs;

		static const char* _progName;
		static u_long _flags;
	};
}

#endif