/*
 * mmcat.c - Implement the cat command using memory maps
 *
 * Created at:  Thu 12 Jun 2008 10:56:12 AM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void err_quit(char *msg);

int main(int argc, char *argv[])
{
	int fdin;
	char *src;
	struct stat statbuf;
	off_t len;

	/* make sure we were called properly */
	if (argc != 2) {
		fprintf(stderr, "usage: mmcat {file}\n");
		return -1;
	}
	/* open the input file and stdout */
	if ((fdin = open(argv[1], O_RDONLY)) < 0) {
		err_quit("open");
	}

	/* need the size of the input file for mmap call */
	if ((fstat(fdin, &statbuf)) < 0) {
		err_quit("fstat");
	}
	len = statbuf.st_size;

	/* map the input file */
	if ((src = mmap(0, len, PROT_READ, MAP_SHARED, fdin, 0)) == (void *) -1) {
		err_quit("mmap");
	}

	/* write it out */
	printf("%s", src);

	/* cleanup */
	close(fdin);
	munmap(src, len);
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

