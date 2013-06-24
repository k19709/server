#ifndef _LES_LOG_MSG_H_
#define _LES_LOG_MSG_H_
#include "config.h"

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
#define LES_DEBUG(X)
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

		static CLogMsg* instance();

		bool traceEnbled(void) const;
		void traceEnbled(bool enbled);

		bool traceActive(void) const;
		void traceActive(bool active);
		
		char* getDir(void) const;
		void makeDir(const char* dir);

		char* getFileName(void) const;
		void setFileName(const char* file);

		int open(const char* programName, int flags);

	private:
		CLogMsg(void);
		~CLogMsg(void);

	private:
		bool _traceEnbled;
		bool _traceActive;
		const char* _dir;
		const char* _fileName;

		static const char* _programName;
		
		char* _msg;
	};
}

#endif