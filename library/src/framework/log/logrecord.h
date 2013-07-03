#ifndef _LES_LOG_RECORD_H_
#define _LES_LOG_RECORD_H_

#include <sstream>
#include <fstream>
#include "common.h"

namespace les
{
	class CLogRecord
	{
	public:
		CLogRecord(void);
		CLogRecord(pid_t pid);
		~CLogRecord(void);

		const char* getMsgData(void) const;
		void setMsgData(const char* data);

		void print(ostream &os);
		void print(FILE* fp);

	private:
		CLogRecord(const CLogRecord&);
		CLogRecord& operator= (const CLogRecord&);

	private:
		char* _msgData;
		size_t _length;
		size_t _msgDataSize;

		pid_t _pid;
	};
}

#endif