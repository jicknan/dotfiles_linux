/*
 * test.c
 *
 * Created at:  Sat 10 Mar 2007 10:35:53 AM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */

#include <stdio.h>

#define MAX	33

int main(void)
{
	long dec;
	static int bin[MAX];
	int i = 0, j;

	while (1) {
		printf("Enter a dec number: ");
		scanf("%ld", &dec);

		do {
			bin[i] = (int)dec%2;
			i++;
		} while (dec/=2);

		for (j = MAX-2, i = 0; j >= 0; j--) {
			printf("%d", bin[j]);
			if (i == 3) {
				printf(" ");
				i = 0;
				continue;
			}
			i++;
		}

		printf("\n");
	}

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

