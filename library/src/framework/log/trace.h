#ifndef _LES_TRACE_H_
#define _LES_TRACE_H_
#include "log/logmsg.h"

namespace les
{
#define LES_TRACE_IMPL(X) CTrace ____(X, __LINE__, __FILE__);

#if !defined(LES_TRACE)
#if (1 == LES_NTRACE)
#define LES_TRACE(X)
#else
#define LES_TRACE(X) LES_TRACE_IMPL(X)
#endif
#endif

	class CTrace
	{
	public:
		CTrace(const char* method, int line = 0, const char* file = NULL);
		~CTrace(void);

	public:
		static bool traceEnabled(void);
		static void startTrace(void);
		static void stopTrace(void);

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