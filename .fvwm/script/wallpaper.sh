#!/bin/bash
[ -d $1/.thumbs ] || mkdir $1/.thumbs
for pic in `find $1/*`; do
    pic=`basename $pic`
    [ -f $1/.thumbs/$pic.png ] || convert -quality 0 -resize 48 $1/$pic $1/.thumbs/$pic.png
    echo "+ %$1/.thumbs/$pic.png%\"$pic\" exec exec \`ln -sf $1/$pic $1/.current && Esetroot -scale $1/$pic\`"
done
