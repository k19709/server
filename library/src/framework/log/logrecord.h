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
		CLogRecord(pid_t pid);
		~CLogRecord(void);

		void msgData(const char* data);
		void print(ostream &os);
		void print(FILE* fp);

	private:
		CLogRecord(const CLogRecord&);
		CLogRecord& operator= (const CLogRecord&);

	private:
		char* _data;
		size_t _dataSize;
		size_t _dataMaxSize;

		pid_t _pid;
	};
}

#endif