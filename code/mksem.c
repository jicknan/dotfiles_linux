/*
 * mksem.c - create and increment a semaphore
 *
 * Created at:  Fri 13 Jun 2008 04:36:27 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int semid;	// semaphore id
	int nsems = 1;	// how many semaphore to create
	int flags = 0666;	// world read-alter mode
	struct sembuf buf;	// how semophore should behave

	/* create the semaphore with world read-alter mode */
	semid = semget(IPC_PRIVATE, nsems, flags);
	if (semid < 0) {
		perror("semget");
		return -1;
	}
	printf("semaphore created: %d\n", semid);

	/* set up the structure for semop */
	buf.sem_num = 0;	// a single semaphore
	buf.sem_op = 1;		// Increment the semaphore
	buf.sem_flg = IPC_NOWAIT;	// don't blcok

	if ((semop(semid, &buf, nsems)) < 0) {
		perror("semop");
		return -1;
	}

	system("ipcs -s");

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

