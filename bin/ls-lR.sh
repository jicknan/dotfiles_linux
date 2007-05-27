#!/bin/sh
# /opt/bin/ls-lR.sh
# Created at Mon 27 Nov 2006 10:26:47 AM UTC by jick.
# 

FTP_DIR=/home/ftp

cd $FTP_DIR
ls -lR > ls-lR
gzip ls-lR
