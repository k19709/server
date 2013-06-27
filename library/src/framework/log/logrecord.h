#ifndef _LES_LOG_RECORD_H_
#define _LES_LOG_RECORD_H_
#include "common.h"
#include "config.h"

namespace les
{
	class CLogRecord
	{
	public:
		CLogRecord(void);
		CLogRecord(u_int pid, u_int threadId);
		~CLogRecord(void);

		void setData(const char* data);
		void print(ostream &os);
		void print(FILE* fp);

	private:
		CLogRecord(const CLogRecord&);
		CLogRecord& operator= (const CLogRecord&);

	private:
		char* _data;
		size_t _dataSize;
		size_t _dataMaxSize;

		u_int _pid;
		u_int _threadId;
	};
}

#endif