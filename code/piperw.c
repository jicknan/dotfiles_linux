/*
 * piperw.c - The correct way to open a pipe and fork a child process.
 *
 * Created at:  Fri 13 Jun 2008 01:21:46 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#define PIPE_BUF	1024

#define BUFSZ PIPE_BUF

void err_quit(char *msg);

int main(int argc, char *argv[])
{
	int fd[2]; // fd array for the pipe
	int fdin; // fd for input file
	char buf[BUFSZ];
	int pid, len;

	/* Create the pipe */
	if ((pipe(fd)) < 0)
		err_quit("pipe");

	/* fork and close the appropriate descriptor */
	if ((pid = fork()) < 0)
		err_quit("fork");
	if (pid == 0) {
		/* child is reader, close the write descriptor */
		close(fd[1]);
		while ((len = read(fd[0], buf, BUFSZ)) > 0)
			write(STDOUT_FILENO, buf, len);
		close(fd[0]);
	} else {
		/* parent is writer, close the read descriptor */
		close(fd[0]);
		if ((fdin = open(argv[1], O_RDONLY)) < 0) {
			perror("open");
			/* send sth. since we couldn't open the input */
			write(fd[1], "123\n", 4);
		} else {
			while ((len = read(fdin, buf, BUFSZ)) > 0)
				write(fd[1], buf, len);
			close(fdin);
		}
		/* close the write descriptor */
		close(fd[1]);
	}
	/* reap the exit status */
	waitpid(pid, NULL, 0);

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

