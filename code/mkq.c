/*
 * mkq.c - create a SysV IPC message queue
 *
 * Created at:  Fri 13 Jun 2008 03:54:18 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int qid;	// the queue id
	int key;	// the queue key

	key = 123;

	/* create the queue */
	if ((qid = msgget(key, IPC_CREAT | 0666)) < 0) {
		perror("msgget");
		return -1;
	}
	printf("created queue id = %d\n", qid);

	/* open the queue again */
	if ((qid == msgget(key, 0)) < 0) {
		perror("msgget:open");
		return -1;
	}
	printf("opened queue id = %d\n", qid);

	return 0;
}


/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

