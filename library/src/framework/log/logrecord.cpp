#include "log/logrecord.h"

namespace les
{
	CLogRecord::CLogRecord(void) : 
		_data(NULL),
		_dataSize(0),
		_dataMaxSize(0),
		_pid(0),
	{
		this->_dataMaxSize = MAXLOGMSGLEN;
		this->_data = new char[this->_dataMaxSize];
	}

	CLogRecord::CLogRecord(pid_t pid) : 
		_data(NULL),
		_dataSize(0),
		_dataMaxSize(0),
		_pid(pid),
	{
		this->_dataMaxSize = MAXLOGMSGLEN;
		this->_data = new char[this->_dataMaxSize];
	}

	CLogRecord::~CLogRecord(void)
	{
		if (NULL != this->_data)
		{
			delete[] this->_data;
		}
	}

	void CLogRecord::msgData(const char* data)
	{
		size_t newSize = ::strlen(data);
		if (newSize > this->_dataMaxSize)
		{
			char* newData = new char[newSize];
			delete[] this->_data;
			this->_data = newData;
			this->_dataMaxSize = newSize;
		}
		this->_dataSize = newSize;
		memset(this->_data, 0, this->_dataMaxSize);
		strncpy(this->_data, data, this->_dataSize);
	}
	
	void CLogRecord::print(ostream &os)
	{
		os << "[ " << this->_pid << " ] " << this->_data << endl;
		os.flush();
	}

	void CLogRecord::print(FILE* fp)
	{
		ostringstream str;
		str << "[ " << this->_pid << " ] ";
		fputs(str.str().c_str(), fp);
		
		fputs(this->_data, fp);

		str.str("");
		str << endl;
		fputs(str.str().c_str(), fp);
	}
}