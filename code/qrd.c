/*
 * qrd.c - read all message from a message queue
 *
 * Created at:  Fri 13 Jun 2008 04:22:21 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSZ	512

/* msg structure */
struct msg {
	long msg_type;
	char msg_text[BUFSZ];
};

int main(int argc, char *argv[])
{
	int qid;
	int len;
	struct msg pmsg; // a message structure

	/* expect the queue id passwd on the command-line */
	if (argc != 2) {
		puts("USAGE: qrd <queue id>");
		return -1;
	}
	qid = atoi(argv[1]);

	/* retrieve and display a message from the queue */
	len = msgrcv(qid, &pmsg, BUFSZ, 0, 0);
	if (len > 0) {
		(&pmsg)->msg_text[len] = '\0';
		printf("reading the queue id: %05d\n", qid);
		printf("message type: %051d\n", (&pmsg)->msg_type);
		printf("message length: %d bytes\n", len);
		printf("message text: %s\n", (&pmsg)->msg_text);
	} else {
		perror("msgrcv");
		return -1;
	}

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

