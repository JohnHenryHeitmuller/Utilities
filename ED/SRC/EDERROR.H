#if !defined(__ederror_h)              // Sentry, use file only if it's not already included.
#define __ederror_h
#include <windows.h>

enum errorCode
{
	FILEOPEN_FAILED,
	FILEGETINFO_FAILED,
	FILEREAD_FAILED,
	FILECLOSE_FAILED,
	BUFFER_TOO_SMALL,
	INSUFFICIENT_MEMORY
};

#define edDEBUG

#define edWINAPI          0x00000001 // 0000 0000 0000 0000-0000 0000 0000 0001
#define edNONCONTINUABLE  0x80000000 // 1000 0000 0000 0000-0000 0000 0000 0000
#define edCONTINUABLE     0x40000000 // 0100 0000 0000 0000-0000 0000 0000 0000

#ifdef edDEBUG
#define edEXCEPTION(e,t) TEdException(e,t,__FILE__,__LINE__)
#else
#define edEXCEPTION(e,t) TEdException(e,t)
#endif

class TEdException
{
public:
#ifdef edDEBUG
	TEdException::TEdException( DWORD _error, UINT _type, PCSTR _module, UINT _line);
#else
	TEdException::TEdException( DWORD _error, UINT _type);
#endif
	int TEdException::DisplayMessage();
private:
	DWORD error;
	UINT  type;
	PCSTR module;
	UINT  line;
};

#endif                                      // __ederror_h sentry.
