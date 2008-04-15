/*
 * shm.c
 *
 * Created at:  Mon 15 Oct 2007 01:42:48 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ARRAY_SIZE	40000
#define MALLOC_SIZE	100000
#define SHM_SIZE	100000
#define SHM_MODE	(SHM_R | SHM_W) /* user read/write */

char array[ARRAY_SIZE]; /* uninitialized data = bss */

int main(void)
{
	int shmid;
	char *ptr, *shmptr;

	printf("array[] from %x to %x\n", &array[0], &array[ARRAY_SIZE]);
	printf("stack around %x\n", &shmid);

	if ( (ptr = malloc(MALLOC_SIZE)) == NULL) {
		perror("malloc error");
		return -1;
	}
	printf("malloced from %x to %x\n", ptr, ptr+MALLOC_SIZE);

	if ( (shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0) {
		perror("shmget error");
		return -1;
	}
	if ( (shmptr = shmat(shmid, 0, 0)) == (void *) -1) {
			perror("shmat error");
			return -1;
	}
	printf("shared memory attached from %x to %x\n",
			shmptr, shmptr+SHM_SIZE);
	if (shmctl(shmid, IPC_RMID, 0) < 0) {
		perror("shmctl error");
		return -1;
	}

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

