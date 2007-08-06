/*
 * compound_interest.c
 *
 * Created at:  Wed 06 Jun 2007 10:51:10 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
int main(int argc, char **argv)
{
	double corpus = 100.0;
	double rate = 0.1;
	int i, year = 20;
	double cinterest = 0;

	if (argc == 4) {
		corpus = atof(argv[1]);
		rate = atof(argv[2]);
		year = atoi(argv[3]);
		printf("%s %s %s\n", argv[1], argv[2], argv[3]);
		printf("%f %f %d\n", corpus, rate, year);
	}
	cinterest = corpus;

	for (i=1; i<year; i++) {
		cinterest *= (1.0 + rate);
		printf("%d: %f\n", i, cinterest);
	}

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

