#!/bin/bash
FILE="Capture_`date +%Y-%m-%d:%k:%M:%S`"
sleep 5
import -window root ~/${FILE}.jpg
convert ~/${FILE}.jpg -resize 400x300 ~/${FILE}_min.jpg
