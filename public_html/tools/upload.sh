#!/bin/sh

HOST='ftp.sitesled.com'
USER='jnan'
PASSWD='wdlc01'
FILES='calendar.html chinese.html html.html index.html jre.html lynx.html magpie.html mutt.html utf-8.html wget.html'

ftp -n -i $HOST << EOF
user $USER $PASSWD
binary
mput $FILES
mkdir css
cd css
lcd css
mput *.css
cd ..
mkdir imgs
cd imgs
lcd ../imgs
mput *
cd ..
mkdir lilina
cd lilina
lcd ../lilina
put index.html
cd ..
mkdir scripts
cd scripts
lcd ../scripts
mput *.js
quit
EOF
