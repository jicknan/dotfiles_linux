/*
 * gen_asm.c - plotting two horizontal lines using normal and inline
 * functions.
 *
 * Created at:  Tue 17 Jun 2008 01:26:13 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <tonc.h>

void PlotPixel3(int x, int y, u16 clr)
{
	vid_mem[y*240+x] = clr;
}

int main()
{
	int ii;

	// -- using function
	ASM_CMT("using function");
	for (ii=0; ii<240; ii++)
		PlotPixel3(ii, 16, CLR_LIME);

	/* using inline */
	ASM_CMT("using inline");
	for (ii=0;ii<240;ii++)
		m3_plot(ii, 12, CLR_RED);

	while(1);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

