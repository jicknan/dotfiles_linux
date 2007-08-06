/*
 * macro.c
 *
 * Created at:  Tue 26 Jun 2007 02:34:45 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <unistd.h>

#define	PRN_USB2	"/proc/usb_2_printer"
#define	PRN_DETECT	((access(PRN_USB2, F_OK)==0)?1:0)
#define PRN_DEVICE	"/dev/usb/lp"##PRN_DETECT

int main(void)
{
	printf("PRN_DEVICE=%d\n", PRN_DETECT);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

