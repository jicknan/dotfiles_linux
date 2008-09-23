#!/bin/sh
# $Header: /opt/cvsroot/vimrcs/files/sh.skel,v 1.3 2006/04/25 14:11:04 jick Exp $

# bin/switch2wireless.sh
# Created at Mon 30 Jun 2008 11:47:52 PM CST by jick.
# 

if=eth1

sudo iwconfig $if essid any
sudo ifconfig $if up
sudo kill -9 `sudo cat /var/run/dhcpcd-eth0.pid`
sudo ifconfig eth0 down
sudo dhcpcd -d -t 30 $if

echo '::: DONE, enjoy it! :::'
