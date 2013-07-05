#include "util/error.h"
#include "common.h"

namespace les
{
	int getLastError(void)
	{
		return ::GetLastError();
	}

	void setLastError(int error)
	{
		::SetLastError(error);
	}
}