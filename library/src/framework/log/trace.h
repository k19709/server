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
		static bool isTracing(void);
		static void startTracing(void);
		static void stopTracing(void);

		static int getNestingIndent(void);
		static void setNestingIndent(int indent);

	private:
		const char* _method;
		
		static int _enableTracing;
		static int _nestingIndent;

		enum
		{
			DEFAULT_INDENT  = 3,
			DEFAULT_TRACE	= 1,
		};
	};
}

#endif