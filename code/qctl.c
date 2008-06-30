/*
 * qctl.c - remove a message queue
 *
 * Created at:  Fri 13 Jun 2008 04:30:20 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int qid;

	if (argc != 2) {
		puts("USAGE: qctl <qid>");
		return -1;
	}
	qid = atoi(argv[1]);

	if ((msgctl(qid, IPC_RMID, NULL)) < 0) {
		perror("msgctl");
		return -1;
	}
	printf("queue %d removed\n", qid);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

