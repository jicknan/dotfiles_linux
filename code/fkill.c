/*
 * fkill.c - Send a signal using kill(2)
 *
 * Created at:  Wed 11 Jun 2008 11:53:33 AM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t child;
	int errret;

	if ((child = fork()) < 0) {
		perror("fork");
		return -1;
	} else if (child == 0) { // in the child process
		sleep(30);
	} else { // in the parent
		/* send a signal that gets ignored */
		printf("Sending SIGCHLD to %d\n", child);
		errret = kill(child, SIGCHLD);
		if (errret < 0)
			perror("kill:SIGHLD");
		printf("%d still alive\n", child);
		// now kill the child process
		printf("killing %d\n", child);
		if ((kill(child, SIGTERM)) < 0)
			perror("kill:SIGTERM");
		// have to wait to reap the status
		waitpid(child, NULL, 0);
	}
	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

