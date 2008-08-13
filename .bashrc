#~/.bashrc
[ -f /etc/profile ] && . /etc/profile

# Set the values for some environment variables:
#PATH=$PATH:/usr/local/bin:/usr/local/sbin:
PATH=$PATH:$HOME/bin
MANPATH=/usr/man:/usr/share/man

# don't put duplicate lines in the history. See bash(1) for more options
export HISTCONTROL=ignoredups
# Default text editor
EDITOR="vi"

# enable bash completion when using sudo
complete -cf sudo

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

alias ls='ls --color=auto'
alias ll='ls -lh'
alias la='ls -A'
alias l='ls -CF'
alias grep="grep --color"
#        alias cu='sudo chmod 777 /dev/ttyUSB0 && sudo cu -l /dev/ttyUSB0 -s 115200'
# Needed to get "man" to work properly in Unicode locales:
alias man='LC_ALL=C man'

# Set TERM to linux for unknown type or unset variable:
if [ "$TERM" = "" -o "$TERM" = "unknown" ]; then
 TERM=linux
fi
#PS1='[\u@\h \W]\$ '
PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
PS2='> '

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm* | rxvt*)
    PROMPT_COMMAND='echo -ne "\033]0;${USER}@${HOSTNAME}: ${PWD}\007"'
    ;;
*)
    ;;
esac

# arm-linux compile tools/ GCC 3.3.2 OABI
#PATH=$PATH:/opt/arm-linux/bin
#PATH=$PATH:/work/tools/3.3.2/bin
# NS65 toolchain/CSL GCC 3.4.3 EABI
NS65="$HOME/project/NS65"
PATH=$PATH:$NS65
PATH=$PATH:~/arm-tools/arm-linux-gnueabi/bin
PATH=$PATH:~/arm-tools/arm-none-linux-gnueabi/bin
# foonas-em env
FOONAS="$HOME/project/foonas-em"
#PATH=$FOONAS/bitbake/bin:$PATH
BBPATH=$FOONAS/build:$FOONAS/openembedded
# CVS repository for NAS
CVSROOT=:pserver:jick_nan:82f973@scs:12121/home/nas-cvsroot
CVS_RSH=ssh

export PATH MANPATH TERM PS1 PS2 CVSROOT CVS_RSH EDITOR BBPATH

# have fun!
# fortune - print a random, hopefully interesting, adage
#[ -x /usr/bin/fortune ] && fortune -c
