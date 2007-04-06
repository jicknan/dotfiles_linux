/*
 * spawn_fork.c - Spawn-style Linux fork().
 *
 * Created at:  Fri 16 Mar 2007 03:47:08 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(char *prog, char **arg_list)
{
	pid_t child;

	child = fork();

	if (child != 0) {
		return child;
	} else {
		execvp(prog, arg_list);
		fprintf(stderr, "spawn error\n");
		return -1;
	}
}

int main()
{
	char *arg_list[] = {
		"ls",
		"-l",
		"/tmp",
		NULL};

	spawn("ls", arg_list);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

