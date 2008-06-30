/*
 * opipe.c
 *
 * Created at:  Fri 13 Jun 2008 01:14:17 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int fd[2]; // Array for file description

	if ((pipe(fd)) < 0) {
		perror("pipe");
		return -1;
	}
	printf("fds are %d, %d\n", fd[0], fd[1]);
	close(fd[0]);
	close(fd[1]);
	return -1;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

