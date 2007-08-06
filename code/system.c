/*
 * system.c
 *
 * Created at:  Thu 07 Jun 2007 01:33:31 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int ret;
	char buf[128];

	//system("cd ..; ls");

	sprintf(buf, "/bin/pidof %s > /dev/null 2>&1", argv[1]);
	ret = system(buf);
	printf("CMD: %s\nret=%d\n", buf, ret);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

