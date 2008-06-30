/*
 * popen.c - using popen() to open a pipe
 *
 * Created at:  Fri 13 Jun 2008 01:34:26 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#define BUFSZ PIPE_BUF

void err_quit(char *msg);

int main(void)
{
	FILE *fp; // FILE stream for popen
	char *cmd = "cat popen.c";
	char buf[BUFSZ]; // buffer for "input"

	/* create the pipe */
	if ((fp = popen(cmd, "r")) == NULL)
		err_quit("popen");

	/* read cmd's output */
	while ((fgets(buf, BUFSZ, fp)) != NULL)
		printf("%s", buf);

	/* close and frap the exit status */
	pclose(fp);

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

