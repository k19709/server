#ifndef	_LES_ADDR_H_
#define _LES_ADDR_H_

#include "common.h"

namespace les
{
	class CAddr
	{
	public:
		CAddr(void);
		CAddr(int type, int size);
		virtual ~CAddr(void);

		void setType(int);
		int getType(void) const;

		void setSize(int);
		int getSize(void) const;

		virtual void setAddr(void*, int);
		virtual void* getAddr(void) const;

		void baseSet(int, int);

		bool operator ==(const CAddr&) const;
		bool operator !=(const CAddr&) const;
 
	private:
		int _type;
		int _size;
	};
}

#endif