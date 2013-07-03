#include "log/logrecord.h"

namespace les
{
	CLogRecord::CLogRecord(void) : 
		_msgData(NULL),
		_length(0),
		_msgDataSize(0),
		_pid(0)
	{
		this->_msgDataSize = MAXLOGMSGLEN;
		this->_msgData = new char[this->_msgDataSize];
		if (NULL != this->_msgData)
		{
			this->_msgData[0] = '\0';
		}
	}

	CLogRecord::CLogRecord(pid_t pid) : 
		_msgData(NULL),
		_length(0),
		_msgDataSize(0),
		_pid(pid)
	{
		this->_msgDataSize = MAXLOGMSGLEN;
		this->_msgData = new char[this->_msgDataSize];
		if (NULL == this->_msgData)
		{
			this->_msgData[0] = '\0';
		}
	}

	CLogRecord::~CLogRecord(void)
	{
		if (NULL != this->_msgData)
		{
			delete[] this->_msgData;
		}
	}

	void CLogRecord::setMsgData(const char* data)
	{
		size_t newLen = ::strlen(data);
		if (newLen > this->_msgDataSize)
		{
			char* newMsgData = new char[newLen];
			delete[] this->_msgData;
			this->_msgData = newMsgData;
			this->_msgDataSize = newLen;
		}
		this->_length = newLen;
		memset(this->_msgData, 0, this->_msgDataSize);
		strncpy(this->_msgData, data, this->_length);
	}

	const char* CLogRecord::getMsgData(void) const
	{
		return this->_msgData;
	}
	
	void CLogRecord::print(ostream &os)
	{
		os << "[ " << this->_pid << " ]   " << this->_msgData << endl;
		os.flush();
	}

	void CLogRecord::print(FILE* fp)
	{
		ostringstream str;
		str << "[ " << this->_pid << " ]   " << this->_msgData << endl;
		fputs(str.str().c_str(), fp);
	}
}