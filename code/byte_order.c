/*
 * byte_order.c
 *
 * Created at:  Sat 09 Aug 2008 07:49:49 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>

/*
 * return value:
 *	1 - big endian
 *	2 - little endian
 *	3 - unknown
 *	4 - sizeof( short ) != 2
 */
static int byte_order(void)
{
	union
	{
		short s;
		char c[ sizeof(short) ];
	} un;

	un.s = 0x0201;
	if ( 2 == sizeof (short) )
	{
		if ( ( 2 == un.c[0] ) && ( 1 == un.c[1]))
		{
			puts("big-endian");
			return(1);
		}
		else if (( 1 == un.c[0] ) && ( 2 == un.c[1]))
		{
			puts("little-endian");
			return(2);
		}
		else
		{
			puts("unknown");
			return(3);
		}
	}
	else
	{
		printf("sizeof(short)=%d\n", sizeof(short));
		return(4);
	}
	return (3);
}

int main(void)
{
	int ret;
	ret = byte_order();
	return(ret);
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

