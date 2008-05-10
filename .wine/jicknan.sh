#!/bin/sh
regedit jicknan.reg
# You also need copy simsun.ttc to ~/.wine/driver_c/windows/Fonts
font="`locate simsun.ttc`"
dest="~/.wine/driver_c/windows/Fonts/simsun.ttc"
if [ ! -f $dest ]; then
    [ -f $font ] && cp $font $dest
fi

