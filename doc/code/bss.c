/*
 * bbs.c
 *
 * Created at:  Sat 10 Mar 2007 02:59:13 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>

int foo;
int bar;

int main(void)
{
	int *ptr;

	printf(".bss section starts at %08p\n", &foo);

	printf("foo is %d.\n", foo);

	ptr = &foo;
	*ptr = 12345;

	printf("foo is %d.\n", foo);
	printf(".bss section starts at %08p\n", &foo);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

