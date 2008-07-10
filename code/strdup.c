/*
 * strdup.c
 *
 * Created at:  Thu 03 Jul 2008 10:31:42 AM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *s = strdup("Hello strdup!");

	printf("s(%p)=%s\n", s, s);
	free(s);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

