/*
 * rdfifo.c - create a FIFO and read from it
 *
 * Created at:  Fri 13 Jun 2008 02:19:31 PM CST
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

int main(void)
{
	int fd; // descriptor for FIFO
	int len; // bytes read from FIFO
	char buf[PIPE_BUF];
	mode_t mode = 0666;

	if ((mkfifo("fifo1", mode)) < 0) {
		perror("mkfifo");
		return -1;
	}

	/* open the FIFO read-only */
	if ((fd = open("fifo1", O_RDONLY)) < 0) {
		perror("open");
		return -1;
	}

	/* read adn display the FIFO's output until EOF */
	while ((len = read(fd, buf, PIPE_BUF - 1)) > 0)
		printf("rdfifo read: %s", buf);
	close(fd);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

