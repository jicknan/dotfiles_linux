/*
 * fputs.c
 *
 * Created at:  Thu 08 May 2008 02:52:12 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>

int main(void)
{
	FILE *fp = NULL;

	fputs("Hello World\n", stdout);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

