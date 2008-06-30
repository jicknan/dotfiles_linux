/*
 * helloasm.c
 *
 * Created at:  Sun 04 May 2008 06:59:35 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>

char message[] = "Hello, world!\n";

int main(void)
{
	long _res;
	__asm__ volatile (
			"int $0x80"
			: "=a" (_res)
			: "a" ((long) 4),
			  "b" ((long) 1),
			  "c" ((long) message),
			  "d" ((long) sizeof(message)));
	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

