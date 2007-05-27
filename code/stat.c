/*
 * stat.c
 *
 * Created at:  Tue 12 Dec 2006 05:07:39 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s <file-path>\n", argv[0]);
		return -1;
	}
	int fd, ret;
	struct stat *st;
	struct stat st2;

	if (stat(argv[1], &st2) == 0)
		printf("stat: %ld\n", st2.st_size);
	else
		printf("no size.\n");

	//fd=open("stat.c", O_RDONLY);
	fd = open(argv[1], O_RDONLY | O_CREAT);
	if(fd == -1) {
		printf("no file\n");
		return -1;
	}
	ret = fstat(fd, st);
	//ret = stat("stat.c", st);
	if(ret) {
		printf("ret=%d\n", ret);
		return -1;
	}
	if (st->st_size)
		printf("fstat: %ld\n", st->st_size);
	else
		printf("no size\n");

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

