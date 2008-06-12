/*
 * fork.c
 *
 * Created at:  Wed 11 Apr 2007 02:45:47 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int glob = 6;

int main(void)
{
	int var;
	pid_t pid;

	var = 88;
	printf("before fork\n");

	//if ( (pid = fork()) < 0) {
	if ( (pid = fork()) < 0) {
		printf("fork error\n");
		return -1;
	} else if (pid == 0) { /* child */
		glob ++;
		var ++;
	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
		_exit(0);
	} else {
		sleep(2);
	}

	// parent
	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

