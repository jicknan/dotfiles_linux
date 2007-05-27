/*
 * date.c - print iso8601 formated date, and test malloc/free function.
 *
 * Created at:  Tue 12 Dec 2006 02:46:59 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *date2;
char *G_date()
{
	time_t clock;
	struct tm *local;
	char *date = NULL;
	char *d = NULL;

	//char *asctime();
	//struct tm *localtime();

	time(&clock);

	local = localtime(&clock);
	date = malloc(6);
	date2 = malloc(100);
	//memset(date, 0x00, 12);
	sprintf(date, "%02d-%d-%d--------------", local->tm_mon+1,
			local->tm_mday, local->tm_year+1900);
	sprintf(date, "%s.%s", date, "m3u");
	//printf("%s\n", date);
	//date = asctime(local);
#if 1
	for (d = date; *d; d++)
		if (*d == '\n')
			*d = 0;
#endif
	printf("date: %p, date2: %p, local: %p, d: %p\n", date, date2, local, d);
	return date;
}

int main()
{
	char *date;

	date = G_date();

	printf("date: %p, date2: %p\n", date, date2);
	sprintf(date2, "99999\n");
	printf("%s\n", date);
	free(date);
	free(date2);


	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

