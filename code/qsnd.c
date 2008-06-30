/*
 * qsnd.c - send a message to previously opened queue
 *
 * Created at:  Fri 13 Jun 2008 04:08:35 PM CST
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

#define	BUFSZ	512

/* message structure */
struct msg {
	long msg_type;
	char msg_text[BUFSZ];
};

int main(int argc, char *argv[])
{
	int qid; // the queue id
	int len; // length of data sent
	struct msg pmsg; // pointer to message structure

	/* expect the queue id passed on the command line */
	if (argc != 2) {
		puts("USAGE: qsnd <queue id>");
		return -1;
	}
	qid = atoi(argv[1]);

	/* get the message to add to the queue */
	puts("Enter message to post:");
	if((fgets((&pmsg)->msg_text, BUFSZ, stdin)) == NULL) {
		puts("no message to post");
		return -1;
	}

	/* associate the message with this process */
	pmsg.msg_type = getpid();
	/* add the message to the queue */
	len = strlen(pmsg.msg_text);
	if((msgsnd(qid, &pmsg, len, 0)) < 0) {
		perror("msgsnd");
		return -1;
	}
	puts("message posted");

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

