#include "log/trace.h"

namespace les
{
	int CTrace::_enabled = DEFAULT_TRACE;
	int CTrace::_indent = DEFAULT_INDENT;

	CTrace::CTrace(const char* method, int line /* = 0 */, const char* file /* = 0 */) : _method(0)
	{
		this->_method = method;
		if (_enabled)
		{
			if (LES_LOG_MSG->traceEnbled() && !LES_LOG_MSG->traceActive())
				{
					LES_LOG_MSG->traceActive(true);
					//...
					LES_LOG_MSG->traceActive(false);
				}		
		}
	}

	CTrace::~CTrace(void)
	{
		this->flush();
	}

	void CTrace::flush(void)
	{
		if (_enabled)
		{
			if (LES_LOG_MSG->traceEnbled() && !LES_LOG_MSG->traceActive())
			{
				LES_LOG_MSG->traceActive(true);
				//...
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