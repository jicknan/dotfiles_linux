/*
 * fibonacci.c
 *
 * Created at:  Tue 06 Feb 2007 02:05:46 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>

int main(int argc, char **argv)
{
	int a = 1;
	int b = 1;
	int n, i = 1;

	if ( argc != 2) {
		printf("Usage: %s <max layers>\n", argv[0]);
		return -1;
	}

	//printf("0");
	//printf("Ratio(b/a): 1");
	while (i++ <= atoi(argv[1])) {
		n = a;
		a = b;
		b += n;
		printf("%d: b/a\t=\t%d/%d\t=\t%f\n", i-1, b, a, (float)b/(float)a);
	}
	//printf("\n");

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

