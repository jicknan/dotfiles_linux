/*
 * atshm.c - attaching a shared memory segment
 *
 * Created at:  Fri 13 Jun 2008 03:22:09 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int shmid;	// segment ID
	char *shmbuf;	// address in process

	/* expect an segment id on the command line */
	if (argc != 2) {
		puts("USAGE: atshm <identifier>");
		return -1;
	}
	shmid = atoi(argv[1]);

	/* attach the segment */
	if ((shmbuf = shmat(shmid, 0, 0)) < (char *)0) {
		perror("shmat");
		return -1;
	}

	/* where is it attached? */
	printf("segment attached at %p\n", shmbuf);

	/* see, we really are attached! */
	system("ipcs -m");

	/* detach */
	if ((shmdt(shmbuf)) < 0) {
		perror("shmdt");
		return -1;
	}
	puts("segment detached");

	/* yep, we really did detach it */
	system("ipcs -m");

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

