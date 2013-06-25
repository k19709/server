#include "log/trace.h"

namespace les
{
	int CTrace::_enabled = CTrace::DEFAULT_TRACE;
	int CTrace::_indent = CTrace::DEFAULT_INDENT;

	CTrace::CTrace(const char* method, int line /* = 0 */, const char* file /* = 0 */) : _method(NULL)
	{
		this->_method = method;
		if (_enabled)
		{
			if (LES_LOG_MSG->traceEnabled() && !LES_LOG_MSG->traceActive())
			{
				LES_LOG_MSG->traceActive(true);
				LES_DEBUG("calling " << this->_method)
				LES_LOG_MSG->traceActive(false);
			}		
		}
	}

	CTrace::~CTrace(void)
	{
		if (_enabled)
		{
			if (LES_LOG_MSG->traceEnabled() && !LES_LOG_MSG->traceActive())
			{
				LES_LOG_MSG->traceActive(true);
				LES_DEBUG("leaving " << this->_method)
				LES_LOG_MSG->traceActive(false);
			}		
		}
	}

	void CTrace::startTrace(void)
	{
		CTrace::_enabled = 1;
	}

	void CTrace::stopTrace(void)
	{
		CTrace::_enabled = 0;
	}

	bool CTrace::traceEnabled(void)
	{
		return CTrace::_enabled == 1 ? true : false;
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