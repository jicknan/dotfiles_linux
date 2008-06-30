/*
 * opshm.c - reading and writing a shared memory segment
 *
 * Created at:  Fri 13 Jun 2008 03:29:32 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define BUFSZ	4096

int main(int argc, char *argv[])
{
	int shmid; // segment id
	char *shmbuf; // address in process
	int fd;
	int i;

	/* expect a segment id on the command line */
	if (argc != 2) {
		puts("USAGE: opshm <shmid>");
		return -1;
	}
	shmid = atoi(argv[1]);

	/* attach the segment */
	if ((shmbuf = shmat(shmid, 0, 0)) < (char *)0) {
		perror("shmat");
		return -1;
	}

	/* size shmbuf appropriately */
	if ((shmbuf = malloc(sizeof(char) * BUFSZ)) == NULL) {
		perror("malloc");
		return -1;
	}

	for (i = 0; i < BUFSZ; ++i) {
		shmbuf[i] = rand();
	}

	/* write the segment's raw contents out to a file */
	fd = open("opshm.out", O_CREAT | O_WRONLY, 0600);
	write(fd, shmbuf, BUFSZ);
	free(shmbuf);	// don't want memory leaks

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

