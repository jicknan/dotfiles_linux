#!/bin/sh
# arm-linux compile tools
PATH=$PATH:/work/tools/3.2.1/bin
#PATH=$PATH:/work/tools/3.3.2/bin
PATH=$PATH:/opt/arm-linux-gnueabi/bin:/work/tools/H-i686-pc-linux-gnulibc2.2/bin
PATH=$PATH:/opt/crosstool/gcc-3.4.5-glibc-2.3.6/arm-xscale-linux-gnu/bin
# Default CVSROOT path 
CVSROOT=:pserver:jick@scs:/home/nas-cvsroot
SVN_EDITOR="vi"

export PATH CVSROOT SVN_EDITOR
