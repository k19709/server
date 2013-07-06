#ifndef _LES_SOCKET_STREAM_H_
#define _LES_SOCKET_STREAM_H_

namespace les
{
	class CSocketStream
	{
	public:
		CSocketStream(void);
		CSocketStream(HANDLE );
		~CSocketStream(void);

		HANDLE getHandle(void) const;
		void set
	private:
		HANDLE _handle;
	};
	
}

#endif