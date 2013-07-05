#ifndef _LES_LOG_MSG_H_
#define _LES_LOG_MSG_H_

#include "log/logrecord.h"

namespace les
{
#define LES_DEBUG_IMPL(X) \
	do \
	{\
	CLogMsg* ____ = CLogMsg::instance();\
	____->ostr() << X;\
	____->log();\
} while (0);

#if (1 == LES_NLOGGING)
#if !defined(LES_DEBUG)
#define LES_DEBUG(X)
#endif
#else
#if !defined(LES_DEBUG)
#if (1 == LES_NDEBUG)
#define LES_DEBUG(X)
#else
#define LES_DEBUG(X) LES_DEBUG_IMPL(X)
#endif
#endif
#endif

#if (1 == LES_NLOGGING)
#if !defined(LES_ERROR)
#define LES_ERROR(X)
#endif
#else
#if !defined(LES_ERROR)
#if (1 == LES_NDEBUG)
#define LES_ERROR(X)
#else
#define LES_ERROR(X) LES_DEBUG_IMPL(X)
#endif
#endif
#endif

	class CLogMsg
	{
	public:
		// log flags
		enum
		{
			STDERR		= 1,	//write msg to stderr
			OFSTREAM	= 2,	//write msg to ofstream
			SILENT		= 4,	//do not print messages at all
		};

		ostringstream& ostr(void);
		
		void incTraceDepth(void);
		void decTraceDepth(void);
		int getTraceDepth(void);
		void setTraceDepth(int depth);

		bool traceEnabled(void) const;
		void startTrace(void);
		void stopTrace(void);

		bool traceActive(void) const;
		void traceActive(bool active);
		
		const char* getDir(void) const;
		void setDir(const char* dir);

		const char* getFile(void) const;
		void setFile(const char* s);

		void clrFlags(u_long f);
		void setFlags(u_long f);

		pid_t getPID(void);

		void open(u_long flags);
		void log(const char* msg = NULL);
		void log(CLogRecord& logRecord);

		static CLogMsg* instance(void);

	private:
		CLogMsg(void);
		~CLogMsg(void);

	private:
		ostringstream _ostr;
		ofstream* _ofstream;
		
		int _traceDepth;
		bool _traceActive;
		bool _traceEnabled;

		const char* _dir;
		const char* _file;

		u_long _flags;
		static pid_t _pid;
	};
}

#endif