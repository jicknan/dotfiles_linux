/*
 * string.c
 *
 * Created at:  Wed 30 Jul 2008 10:15:18 AM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>

int main(void)
{
	char *s = "/dev/sda";

	printf("%s\n", s+5);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

