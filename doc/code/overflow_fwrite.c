/*
 * overflow-fwrite.c
 *
 * Created at:  Wed 25 Oct 2006 04:23:53 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */

#include <stdio.h>

int main(void)
{
	unsigned char zero = 0x00;
	FILE *fp = fopen("xxx","w");
	if(fp==NULL) {
		printf("Error to open the file.\n");
		return -1;
	}
	fwrite(&zero, 1, 10, fp);
	fclose(fp);

	return 0;
}
/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

