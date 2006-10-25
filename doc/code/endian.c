/*
 * endian.c - little, or big?
 *
 * Created at:  Wed 25 Oct 2006 04:08:36 PM UTC
 *
 * Thanks to Fog Hua/SerComm.
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>

int main(void)
{
	union {
		long l;
		char c[sizeof(long)];
	} u;

	u.l = 1;
	if (u.c[0] == 1) {
		printf("little endian!\n");
	} else {
		printf("big endian!\n");
	}

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

