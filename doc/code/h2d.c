/*copyright {{{2
 * Copyright (c) Sercomm
 * $Id: c.skel,v 1.2 2006/04/25 13:20:41 jick Exp $
 *
 * h2d.c
 *	This file defined for 
 *
 * Created at:  Mon 22 May 2006 04:19:52 PM CST
 *
 * }}}*/
 /*header files	{{{1*/
#include <stdio.h>
 /*}}}*/

 /*declaration		{{{1*/
 /*}}}*/

 /*functions		{{{1*/
int main(int argc, char *argv[])
{
	unsigned long i;
	double o;

#if 0
	if (argc != 2) {
		printf("Error!\n");
		printf("Usage: %s <hex_num>\n", argv[0]);
		return -1;
	}
#endif

	while(1) {
		printf("Enter a hex number: ");
		scanf("%lx", &i);
		o = (double)i;
		printf("%#lX=%.0f", i, o);
		o /= 1024.0;
		if (o >= 1)
			printf("=%.1fK", o);
		o /= 1024.0;
		if (o >= 1)
			printf("=%.1fM", o);
		o /= 1024.0;
		if (o >= 1)
			printf("=%.1fG", o);
		putchar('\n');
	}

	return 0;
}


/* vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 * }}}*/

