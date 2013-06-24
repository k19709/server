#ifndef _LES_LOG_MSG_H_
#define _LES_LOG_MSG_H_
#include "config.h"
#include "common.h"

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
	} while (0);
#endif
#endif

#if !defined(MAXLOGMSGLEN)
#define MAXPATHLEN 4*1024
#endif

#define LES_LOG_MSG CLogMsg::instance()

	class CLogMsg
	{
	public:
		// log flags
		enum
		{
			STDERR	= 1,	//write msg to stderr
			STREAM	= 2,	//write msg to stream
		};

		static CLogMsg* instance(void);

		bool traceEnabled(void) const;
		void traceEnabled(bool enabled);

		bool traceActive(void) const;
		void traceActive(bool active);
		
		const char* getDir(void) const;
		void makeDir(const char* dir);

		const char* getFileName(void) const;
		void setFileName(const char* file);

		char* getMsg(void) const;
		void setMsg(const char* msg);

		ostream* getMsgOstream(void) const;
		void setMsgOstream(ostream* os);

		int open(const char* programName, u_long flags);

	private:
		CLogMsg(void);
		~CLogMsg(void);

	private:
		bool _traceEnabled;
		bool _traceActive;
		const char* _dir;
		const char* _fileName;
		char* _msg;
		ostream* _msgOstream;

		static const char* _programName;
		static u_long _flags;
		
	};
}

#endif