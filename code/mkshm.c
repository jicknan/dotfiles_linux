/*
 * mkshm.c - create and initialize shared memory segment
 *
 * Created at:  Fri 13 Jun 2008 02:52:48 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define	BUFSZ	4096	// size of the segment

int main(void)
{
	int shmid;

	if ((shmid = shmget(IPC_PRIVATE, BUFSZ, 0666)) < 0) {
		perror("shmget");
		return -1;
	}

	printf("segment created: %d\n", shmid);
	system("ipcs -m");

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

