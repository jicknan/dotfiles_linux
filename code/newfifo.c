/*
 * newfifo.c - create a FIFO
 *
 * Created at:  Fri 13 Jun 2008 02:11:25 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	mode_t mode = 0666;

	if (argc != 2) {
		puts("USAGE: newfifo {name}");
		return -1;
	}

	if ((mkfifo(argv[1], mode)) < 0) {
		perror("mkfifo");
		return -1;
	}

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

