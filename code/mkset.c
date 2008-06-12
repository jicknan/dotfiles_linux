/*
 * mkset.c - Create a signal set
 *
 * Created at:  Wed 11 Jun 2008 01:17:08 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void err_quit(char *);

int main(void)
{
	sigset_t newset;

	// Create the set
	if ((sigemptyset(&newset)) < 0)
		err_quit("sigemptyset");
	// Add SIGCHLD to the set
	if ((sigaddset(&newset, SIGCHLD)) < 0)
		err_quit("sigaddset");
	// Check the signal mask
	if (sigismember(&newset, SIGCHLD))
		puts("SIGCHLD is in signal mask");
	else
		puts("SIGCHLD not in signal mask");
	// SIGTERM shouldn't be there
	if (sigismember(&newset, SIGTERM))
		puts("SIGTERM is in signal mask");
	else
		puts("SIGTERM not in signal mask");

	return 0;
}

void err_quit(char *msg)
{
	perror(msg);
	exit(-1);
}


/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

