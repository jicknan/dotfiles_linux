/*
 * wrfifo.c - write to a "well-known" FIFO
 *
 * Created at:  Fri 13 Jun 2008 02:24:20 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>

int main(void)
{
	int fd; // descriptor for FIFO
	int len; // bytes written to FIFO
	char buf[PIPE_BUF]; // ensure atomic writes
	time_t tp; // for time call

	/* identify myself */
	printf("I am %d\n", getpid());

	/* open the FIFO write_only */
	if ((fd = open("fifo1", O_WRONLY)) < 0 ) {
		perror("open");
		return -1;
	}

	/* generate some data to write */
	while(1) {
		/* get the current time */
		time(&tp);

		/* create the string to write */
		len = sprintf(buf, "wrfifo %d sends %s\n", getpid(), ctime(&tp));

		/* use (len+1) because sprintf does not count
		 * the terminating null
		 */
		if ((write(fd, buf, len + 1)) < 0) {
			perror("write");
			close(fd);
			return -1;
		}
		sleep(3);
	}
	close(fd);
	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

