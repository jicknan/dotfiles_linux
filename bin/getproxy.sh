#
# This script is used to get free http proxies from
# www.cybersyndrome.net
#
# Fog Hua,Sun Jul 23 00:17:54 2006
#

#!/bin/bash

red="\033[31m"
green="\033[32m"
yellow="\033[33m"
end="\033[0m"

test_page="zh.wikipedian.org"
#test_page="http://scratchpad.wikia.com/wiki/Qnap_Turbostation:TSSerial"
timeout=20

if [ "$#" = 0 ]
then
    echo -e ${yellow}Using "$test_page" to test ...${end}
    echo
else
    timeout=$1
    if [ "$#" = 2 ]
    then
    test_page=$2
    fi 
fi

proxy_page="http://www.cybersyndrome.net/pla4.html"
echo -n -e ${yellow}"Getting latest proxy file and abstract proxy ..."${end}
PROXYS=`wget --quiet -T 20 -t 1 -O - $proxy_page |grep '<li>'|sed -e 's/<[^<>]\{1,\}class=\"[^BCA]\">[^<>]\{1,\}<\/a>//g'|sed -e 's/<[^<>]\{1,\}>/ /g'`

if [ "$?" = 0 ]
then
    echo -e ${green}OK${end}
else
    echo -e ${red}Failed${end}
    exit 1
fi


WGET="wget --quiet --cache=off -T $timeout -t 1 -w 0 -O /dev/null $test_page"
PROXY=""

for proxy in $PROXYS ; do
    export http_proxy="http://$proxy"
    /usr/bin/time -o /tmp/proxytimer_$proxy.txt -f %e $WGET &
done

echo Wait $timeout+2 seconds...
sleep $timeout
sleep 2

for proxy in $PROXYS;do
    tail -1 /tmp/proxytimer_$proxy.txt | sed -e "s/$/, $proxy/" >> /tmp/proxytimer_total
    #grep -q "status" /tmp/proxytimer_$proxy.txt || cat /tmp/proxytimer_$proxy.txt | sed -e "s/$/, $proxy/" >> /tmp/proxytimer_total
done

echo -e ${yellow}"Top 10 proxies in this run:"${end}
cat /tmp/proxytimer_total |grep -e "^[0-9]" |sort -n -t',' -k1| head -n10
#rm -f /tmp/proxytimer_*
