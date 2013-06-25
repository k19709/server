#ifndef _LES_TRACE_H_
#define _LES_TRACE_H_
#include "common.h"
#include "log/logmsg.h"

namespace les
{
#if !defined(LES_TRACE)
#define LES_TRACE(X) CTrace ____(X, __LINE__, __FILE__);
#endif

	class CTrace
	{
	public:
		CTrace(const char* method, int line = 0, const char* file = 0);
		~CTrace(void);
		void flush(void);

	public:
		static void startTrace(void);
		static void stopTrace(void);
		static bool traceEnabled(void);

		static int getIndent(void);
		static void setIndent(int indent);

	private:
		const char* _method;
		static int _enabled;
		static int _indent;

		enum
		{
			DEFAULT_INDENT  = 3,
			DEFAULT_TRACE	= 1,
		};
	};
}

#endif