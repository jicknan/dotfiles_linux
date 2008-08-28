#!/bin/sh

# hide me
if [ -f $HOME/.hideme ]; then
    source $HOME/.hideme
else
    echo  "====================================================
    OK, there is no $HOME/.hideme. Please note:
    * JICK_HOST is required for using config under git;
    * FTPUSER & FTPPASS is required for using upload2ftp;
    * FFUSER is required for using ffshare
    ====================================================="
fi

if [ -f ~/.bashrc ]; then
    source ~/.bashrc
fi

if [[ -z "$DISPLAY" ]] && [[ $(tty) = /dev/vc/1 ]]; then
	startx
fi
