// edmem.cpp
#include "edmem.h"

BYTE* EdNew( DWORD size )
{
	int ret;
	BYTE *p;

	while(TRUE)
	{
		try
		{
			p = new BYTE[size];
		}
		catch(xalloc)
		{
			ret = MessageBox( NULL,
				"There is not enough memory available to complete operation.  If you"
				" close down other applications you may be able to retry this operation.",
				"INSUFFICIENT MEMORY", MB_APPLMODAL | MB_ICONSTOP | MB_RETRYCANCEL);
			if( ret == IDRETRY )
				continue;
			p = NULL;
		}
		break;
	}
	return(p);
}