#!/bin/sh
# $XConsortium: xinitrc.cpp,v 1.4 91/08/22 11:41:34 rws Exp $

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/usr/X11R6/lib/X11/xinit/.Xresources
sysmodmap=/usr/X11R6/lib/X11/xinit/.Xmodmap

# merge in defaults and keymaps

if [ -f $sysresources ]; then
    xrdb -merge $sysresources
fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f $userresources ]; then
    xrdb -merge $userresources
fi

if [ -f $usermodmap ]; then
    xmodmap $usermodmap
fi

# start some nice programs

if [ -x /usr/bin/scim ]; then 
    #export LANG=zh_CN.utf8
    echo "Setting and starting SCIM: scim -d"
    export GTK_IM_MODULE="xim"
    export XMODIFIERS="@im=SCIM"
    scim -d
fi


if [ -x /usr/bin/urxvtd ]; then
    echo "Starting urxvtd: urxvtd -q -o -f"
    urxvtd -q -o -f
fi

echo "Setting screen root: xsetroot -solid SteelBlue"
xsetroot -solid SteelBlue

echo "Starting fvwm: fvwm2"
fvwm2
