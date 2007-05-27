#!/bin/sh

#ARGS="-hda /jick/qemu/winxp.img -boot c -net nic,vlan=0 -net tap,vlan=0,ifname=tap0,script=/etc/qemu-ifup -m 256 -localtime"

#echo Setting up net bridge ...
#sudo /etc/rc.d/rc.bridge
#
#echo "Loading kqemu kernel module..."
##sudo modprobe kqemu
#sudo /etc/rc.d/rc.kqemu
#echo "...."

if [ "$1" == "init" ]; then
    sudo umount /dev/shm
    sudo mount -t tmpfs -o size=144m none /dev/shm
    sudo /sbin/modprobe kqemu major=0
    exit
fi

IMAGE=/boot/vmlinuz

sudo qemu -nographic -net nic -net tap -hda /jick/qemu/winxp.img -kernel ${IMAGE} -append "console=ttyS0 root=/dev/hda rw sb=0x220,5,1,5 ide2=noprobe ide3=noprobe ide4=noprobe ide5=noprobe clock=pit"
#exec qemu $ARGS
