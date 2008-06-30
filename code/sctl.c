/*
 * sctl.c - maipulate and delete a semaphore
 *
 * Created at:  Fri 13 Jun 2008 04:44:46 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int semid;	// semaphore id

	if (argc != 2) {
		puts("USAGE: sctl <semid>");
		return -1;
	}
	semid = atoi(argv[1]);

	/* remove the semaphore */
	if ((semctl(semid, 0, IPC_RMID)) < 0) {
		perror("semctl IPC_RMID");
		return -1;
	} else {
		puts("semaphore removed");
		system("ipcs -s");
	}
	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

