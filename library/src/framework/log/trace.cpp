#include "log/trace.h"

namespace les
{
	int CTrace::_enabled = CTrace::DEFAULT_TRACE;
	int CTrace::_indent = CTrace::DEFAULT_INDENT;

	CTrace::CTrace(const char* method, int line /* = 0 */, const char* file /* = NULL */) : _method(method)
	{		
		if (CTrace::traceEnabled())
		{
			CLogMsg *lm = CLogMsg::instance();
			if (lm->traceEnabled() && !lm->traceActive())
			{
				lm->traceActive(true);
				LES_DEBUG("calling " << this->_method /*<< " in file " << file << " on line " << line*/)
				lm->traceActive(false);
			}
		}
	}

	CTrace::~CTrace(void)
	{
		if (CTrace::traceEnabled())
		{
			CLogMsg *lm = CLogMsg::instance();
			if (lm->traceEnabled() && !lm->traceActive())
			{
				lm->traceActive(true);
				LES_DEBUG("leaving " << this->_method)
				lm->traceActive(false);
			}	
		}
	}

	bool CTrace::traceEnabled(void)
	{
		return CTrace::_enabled == 1 ? true : false;
	}

	void CTrace::startTrace(void)
	{
		CTrace::_enabled = 1;
	}

	void CTrace::stopTrace(void)
	{
		CTrace::_enabled = 0;
	}

	int CTrace::getIndent(void)
	{
		return CTrace::_indent;
	}

	void CTrace::setIndent(int indent)
	{
		CTrace::_indent = indent;
	}
}