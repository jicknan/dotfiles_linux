#!/bin/sh
# $Xorg: xinitrc.cpp,v 1.3 2000/08/17 19:54:30 cpqbld Exp $

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

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

# xft support for Gtk 2.2 and below:
export GDK_USE_XFT=1

# start some nice programs

# Set a background color:
BG=xsetroot
test -z $BG || $BG -solid SteelBlue
#test -z $BG || $BG -solid "#303030"

# scim input platform
if [ -x /usr/bin/scim ]; then 
	#export LANG=zh_CN.utf8
	echo "Setting and starting SCIM: scim -d"
	export XMODIFIERS="@im=SCIM"
	export GTK_IM_MODULE="scim"
	export QT_IM_MODULE="scim"
	scim -d
fi

if [ -x /usr/bin/urxvtd ]; then
	echo "Starting urxvtd: urxvtd -q -o -f"
	urxvtd -q -o -f
fi

# Set background image:
if [ -x /usr/bin/feh ]; then
	feh --bg-scale $HOME/.config/openbox/.current &
fi

#(sleep 2 && fbpanel) &
if [ -x /usr/bin/conky ]; then
	(sleep 2 && conky) &
fi

if [ -x /usr/bin/trayer ]; then
	(sleep 2 && trayer --expand true --widthtype request --transparent true --alpha 255 --edge bottom --align right --SetDockType false) &
fi

# Start a wm:
#twm &
#fvwm2
exec openbox-session
