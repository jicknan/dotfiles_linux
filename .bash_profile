#!/bin/sh

# hide me
if [ -f $HOME/.hideme ]; then
    source $HOME/.hideme
else
    echo  "====================================================\n
    OK, there is no $HOME/.hideme. Please note: \n
    * JICK_HOST is required for using config under git;\n
    * FTPUSER & FTPPASS is required for using upload2ftp;\n
    * FFUSER is required for using ffshare\n
    ====================================================="
fi

if [ -f ~/.bashrc ]; then
    source ~/.bashrc
fi

if [[ -z "$DISPLAY" ]] && [[ $(tty) = /dev/vc/1 ]]; then
	startx
fi
