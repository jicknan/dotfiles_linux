/*
 * block.c - Blocking signals
 *
 * Created at:  Wed 11 Jun 2008 01:24:06 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <unistd.h>
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
	// Adding SIGTERM and SIGALRM
	if ((sigaddset(&newset, SIGTERM)) < 0)
		err_quit("sigaddset:SIGTREM");
	if ((sigaddset(&newset, SIGALRM)) < 0)
		err_quit("sigaddset:SIGALRM");

	// Block the signals without handling them
	if((sigprocmask(SIG_BLOCK, &newset, NULL)) < 0)
		err_quit("sigprocmask");

	// Wait for a signal
	pause();

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

