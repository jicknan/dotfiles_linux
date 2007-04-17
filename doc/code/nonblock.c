/*
 * nonblock.c
 *
 * Created at:  Fri 13 Apr 2007 04:07:02 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

char	buf[100000];

int main(void)
{
	int	ntowrite, nwrite;
	char	*ptr;

	ntowrite = read(0, buf, sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);

	fcntl(1, F_SETFL, O_NONBLOCK);	/* set nonblocking */

	for (ptr = buf; ntowrite > 0; ) {
		errno = 0;
		nwrite = write(1, ptr, ntowrite);
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
		if (nwrite > 0) {
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}

	fcntl(1, O_NONBLOCK);	/* clear nonblocking */

	return 0;
}


/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

