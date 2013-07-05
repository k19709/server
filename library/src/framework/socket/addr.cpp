#include "socket/addr.h"

namespace les
{
	CAddr::CAddr(void) : 
		_type(AF_ANY), _size(-1)
	{
		
	}

	CAddr::CAddr(int type, int size) : 
		_type(type), _size(size)
	{
	}

	CAddr::~CAddr(void)
	{
	}

	void CAddr::setType(int type)
	{
		this->_type = type;
	}

	int CAddr::getType(void) const
	{
		return this->_type;
	}

	void CAddr::setSize(int size)
	{
		_size = size;
	}

	int CAddr::getSize(void) const
	{
		return this->_size;
	}

	void CAddr::setAddr(void*, int)
	{
	}

	void* CAddr::getAddr(void) const
	{
		return 0;
	}

	void CAddr::baseSet(int type, int size)
	{
		this->_type = type;
		this->_size = size;
	}

	bool CAddr::operator ==(const CAddr& ref) const
	{
		return (this->_type == ref.getType() && this->_size == ref.getSize());
	}

	bool CAddr::operator !=(const CAddr& ref) const
	{
		return !(*this == ref);
	}
}