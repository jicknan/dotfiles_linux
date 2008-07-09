/*
 * pending.c - Fun with sigpending
 *
 * Created at:  Wed 11 Jun 2008 01:35:21 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	sigset_t set, pendset;
	struct sigaction action;

	sigemptyset(&set);

	// Add the interesting signal
	sigaddset(&set, SIGTERM);
	// Block the signal
	sigprocmask(SIG_BLOCK, &set, NULL);

	// Send SIGTERM to myself
	kill(getpid(), SIGTERM);

	// Get pending signals
	sigpending(&pendset);

	// If SIGTERM pending, ignore it
	if (sigismember(&pendset, SIGTERM)) {
		sigemptyset(&action.sa_mask);
		action.sa_handler = SIG_IGN; // Ignore SIGTERM
		sigaction(SIGTERM, &action, NULL);
	}

	/* Unblock SIGTERM */
	sigprocmask(SIG_UNBLOCK, &set, NULL);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

