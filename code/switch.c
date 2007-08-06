/*
 * switch.c
 *
 * Created at:  Mon 16 Jul 2007 02:52:53 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	int i;

	switch(i = fork()) {
		case 0: printf("child\n"); break;
		case -1: printf("error\n"); break;
		default: printf("server\n"); break;
	}

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

