#include "log/trace.h"

namespace les
{
	int CTrace::_enableTracing = CTrace::DEFAULT_TRACE;
	int CTrace::_nestingIndent = CTrace::DEFAULT_INDENT;

	CTrace::CTrace(const char* method, int line /* = 0 */, const char* file /* = NULL */) : _method(method)
	{		
		if (CTrace::isTracing())
		{
			CLogMsg *lm = CLogMsg::instance();
			if (lm->tracingEnabled() && !lm->traceActive())
			{
				lm->traceActive(true);
				LES_DEBUG("calling " << this->_method << " in file " << file << " on line " << line)
				lm->traceActive(false);
			}
		}
	}

	CTrace::~CTrace(void)
	{
		if (CTrace::isTracing())
		{
			CLogMsg *lm = CLogMsg::instance();
			if (lm->tracingEnabled() && !lm->traceActive())
			{
				lm->traceActive(true);
				LES_DEBUG("leaving " << this->_method)
				lm->traceActive(false);
			}		
		}
	}

	bool CTrace::isTracing(void)
	{
		return CTrace::_enableTracing == 1 ? true : false;
	}

	void CTrace::startTracing(void)
	{
		CTrace::_enableTracing = 1;
	}

	void CTrace::stopTracing(void)
	{
		CTrace::_enableTracing = 0;
	}

	int CTrace::getNestingIndent(void)
	{
		return CTrace::_nestingIndent;
	}

	void CTrace::setNestingIndent(int indent)
	{
		CTrace::_nestingIndent = indent;
	}
}