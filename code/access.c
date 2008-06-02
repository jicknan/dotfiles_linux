/*
 * access.c
 *
 * Created at:  Fri 30 May 2008 05:33:52 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */

#include <stdio.h>
#include <unistd.h>

#define F "/var/"

int main(void)
{
	printf("access(%s)=%d\n", F, access(F, F_OK));

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

