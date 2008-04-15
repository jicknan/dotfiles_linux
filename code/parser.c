/*
 * parser.c
 *
 * Created at:  Mon 15 Oct 2007 03:12:10 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>

#define MEDIA_CONF	"/tmp/media.conf"
#define CONTENT_PATH	4
#define TARGET_STRING	"+A|/harddisk,+P/data/podcast"

struct entry {
	char *path;
	int type;
};

int main(void)
{
	char *p = NULL, *p1 = NULL;
	char buf[4][256];

	p1 = TARGET_STRING;
	p = strrchr(p1, ',');
	*p = 0;
	strncpy(buf[1], p+1, strlen(p));
	printf("%s\n", buf[1]);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

