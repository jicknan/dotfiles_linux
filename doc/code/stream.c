/*
 * stream.c
 *
 * Created at:  Fri 13 Apr 2007 05:35:43 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stropts.h>

int isastream(int fd)
{
	return (ioctl(fd, I_CANPUT, 0) != -1);
}

int main(int argc, char *argv[])
{
	int	fd, i, nmods;
	struct	str_list	list;
	if (argc != 2) {
		printf("Usage: %s <pathname>\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_RDONLY);
	if (isastream(fd) == 0) {
		printf("%s is not a stream\n", argv[1]);
		return -1;
	}

	nmods = ioctl(fd, I_LIST, (void *) 0);
	printf("#modules = %d\n", nmods);

	list.sl_modlist = calloc(nmods, sizeof(struct str_mlist));
	if (list.sl_modlist == NULL) {
		perror("calloc error");
		return -1;
	}
	list.sl_nmods = nmods;

	ioctl(fd, I_LIST, &list);

	for (i = 1; i <= nmods; i++)
		printf("    %s: %s\n", (i == nmods) ? "driver" : "module", list.sl_modlist++);

	return 0;
}


/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

