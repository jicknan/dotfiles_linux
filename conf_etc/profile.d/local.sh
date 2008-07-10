#!/bin/sh
# some more aliases
alias ll='ls -lh'
alias la='ls -A'
alias l='ls -CF'
# colorful grep result:
alias grep='grep --color'
# K&R C style:
alias indent='indent -kr -i8'
# Needed to get "man" to work properly in Unicode locales:
alias man='LC_ALL=C man'

# arm-linux compile tools/ GCC 3.3.2 OABI
PATH=$PATH:/opt/arm-linux/bin
#PATH=$PATH:/work/tools/3.3.2/bin
# Linksys_SMB toolchain/CSL GCC 3.4.3 EABI
PATH=$PATH:/opt/arm-linux-gnueabi/bin
#PATH=$PATH:/opt/arm-none-linux-gnueabi/bin
# Default CVSROOT path 
CVSROOT=:pserver:jick_nan:82f973@scs:12121/home/nas-cvsroot
SVN_EDITOR="vi"

export PATH CVSROOT SVN_EDITOR
