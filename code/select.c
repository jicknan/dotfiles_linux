/*
 * select.c
 *
 * Created at:  Fri 18 Apr 2008 06:13:49 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TIME 5

int main(int argc, char *argv[])
{
	int fd, ret;
	struct timeval time;
	fd_set rfds;

	time.tv_sec = TIME;
	time.tv_usec = 0;

	fd = open("/tmp", O_RDONLY);

	FD_ZERO (&rfds);
	FD_SET (fd, &rfds);

	printf("select() start, wait %ds?\n", TIME);
	ret = select (fd + 1, &rfds, NULL, NULL, &time);
	printf("ret=%d\n", ret);
	if (ret < 0) {
		perror("select");
		return -1;
	} else if (ret = 0) {
		printf("you have no time\n");
		return 0;
	}

	sleep(10);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

