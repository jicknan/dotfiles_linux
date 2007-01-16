#!/bin/sh

if [ $# -lt 3 ]; then
    echo "Usage: $0 <target> <title> <div-id> [nosidarbar]"
    exit 1
fi

TARGET="$1"
DEST="$TARGET".html
MAIN="${TARGET}"_main.html
TITLE="$2"
DIVID="$3"
SBAR="$4"

TOPDIR=`/bin/pwd`
ROOTDIR="$TOPDIR"/assets/inc
HEADER="$ROOTDIR"/header.html
SIDEBAR="$ROOTDIR"/sidebar.html
FOOTER="$ROOTDIR"/footer.html

# init DEST file
if [ -e $DEST ]
then
  echo 'Backuping existing '$DEST' ...'
  mv $DEST $DEST'.p'
fi

# import header
[ -f $HEADER ] || exit 1
#cat >> $DEST < $HEADER
cat $HEADER | sed -e "s/_TITLE_/$TITLE/" -e "s/_DIVID_/$DIVID/" >> $DEST

# import sidebar
if [ "x$SBAR" != "xnosidebar" ];
then
    [ -f $SIDEBAR ] || exit 1
    cat >> $DEST < $SIDEBAR
fi

# import main content
[ -f $MAIN ] || exit 1
cat >> $DEST < $MAIN

# import footer
[ -f $FOOTER ] || exit 1
cat >> $DEST < $FOOTER 

echo $DEST'[done.]'
