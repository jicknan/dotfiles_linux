#!/bin/sh

# generate visitors report
web_dir=$HOME/web
log_file=/usr/local/apache/logs/access_log
out_file=$web_dir/report.html

if [ -f $out_file ] 
then 
  mv $out_file $out_file.p 
fi 

visitors --user-agents --weekday-hour-map --month-day-map --referers-age --domains --operating-systems --browsers --error404 --pageviews --robots --max-lines 50 --output html --output-file $out_file --prefix http://172.21.4.85 --trail $log_file

