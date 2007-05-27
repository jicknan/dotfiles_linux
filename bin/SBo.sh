#!/bin/sh

if [ $# != 2 ];then
    echo "$0 <pkg_name>, [bz2|gz]"
    exit 0
fi

echo "Downloading package..."
wget -c `grep DOWNLOAD $1.info | cut -f2 -d=` || exit 0

echo "Checking sum..."
if [ "x`md5sum $1*$2 | cut -f1 -d' '`" == "x`grep MD5SUM $1.info | cut -f2 -d=`" ]
then
    echo "MD5SUM matchs."
else
    echo "md5sum _not_ match."
    exit 0
fi

echo "Compling and packageing..."
sudo ./$1.SlackBuild

echo "Done."
