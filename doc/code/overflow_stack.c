/*
 * overflow-stack.c
 *
 * Created at:  Wed 25 Oct 2006 04:33:14 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>

char str1[8] = "AAAAAAA";

int main(void)
{
	static char str2[8];
	char str3[8] = "CCCCCCC";
	char str4[16*1024*1024];
	char str5[8] = "DDDDDDD";

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

