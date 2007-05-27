#!/bin/sh
# $Header: /opt/cvsroot/vimrcs/files/sh.skel,v 1.3 2006/04/25 14:11:04 jick Exp $

# win.sh
# Created at Mon 02 Apr 2007 05:55:28 PM UTC by jick.
# 

umount /dev/shm
mount -t tmpfs -o size=528m none /dev/shm
qemu -net nic -net tap -hda /jick/qemu/winxp.img -m 512 -localtime
echo "1">/proc/sys/net/ipv4/ip_forward
iptables -t nat -F
iptables -t nat -A POSTROUTING -o eth0 -s 172.20.0.0/24 -j MASQUERADE
umount /dev/shm
mount -t tmpfs -o size=72m none /dev/shm
