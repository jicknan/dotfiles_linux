#!/bin/bash

BASEURL="http://youtube.com/get_video.php?" ; read -p "YouTube URL? " ORIGURL ; read -p "Desired path/filename? " OUTFILE

wget -c -S -O ${OUTFILE}.flv ${BASEURL}`curl -s ${ORIGURL} | grep player2.swf | cut -f2 -d? | cut -f1 -d\"` && ffmpeg -i ${OUTFILE}.flv -ab 56 -ar 22050 -b 500 -s 320x240 ${OUTFILE}.mpg && exit 0
