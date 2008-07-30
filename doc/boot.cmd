u-boot for NS65:
================
set ethaddr 00:c0:02:00:c0:66; set bootargs console=ttyS0,115200 root=/dev/ram; set serverip 172.21.6.12; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage; tftpboot 0x1100000 romdisk; bootm 0x400000

set ethaddr 00:c0:02:00:c0:66; set bootargs console=ttyS0,115200 root=/dev/ram; set serverip 172.21.6.133; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage; tftpboot 0x1100000 romdisk; bootm 0x400000

set ethaddr 00:c0:02:00:c0:66; set bootargs console=ttyS0,115200 root=/dev/ram; set serverip 172.21.6.133; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage; tftpboot 0x2c00000 ramdisk.gz; bootm 0x400000

set ethaddr 00:c0:02:00:c0:66; set bootargs console=ttyS0,115200 root=/dev/ram; set serverip 172.21.6.133; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage; cp.b  0xff200000 0x2c00000 0xd00000; bootm 0x400000

set ethaddr 00:c0:02:00:c0:66; set bootargs console=ttyS0,115200 root=/dev/ram; set serverip 172.21.6.133; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage-2.6.25.9-r0-linksyssmb-initramfs.bin; bootm 0x400000

set ethaddr 00:c0:02:00:c0:66; set serverip 172.21.7.20; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage;tftpboot 0x1100000 romdisk; bootm 0x400000

set ethaddr 00:c0:02:00:c0:66; set serverip 172.21.6.12; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage; bootm 0x400000

set ethaddr 00:c0:02:00:c0:66; set serverip 172.21.6.7; set ipaddr 172.21.6.77; bubt; reset

set bootargs console=ttyS0,115200 root=/dev/ram; set ethaddr 00:c0:02:00:c0:66; set serverip 192.168.0.10; set ipaddr 192.168.0.11; tftpboot 0x400000 uImage; tftpboot 0x1100000 romdisk; bootm 0x400000

u-boot for foonas
=================
set bootargs console=ttyS0,115200 root=/dev/ram0; set serverip 172.21.6.17; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage_2.6.24; bootm 0x400000

RedBoot for NS54:
=================
ip_address -h 172.21.6.32 -l 172.21.6.24; load -r -v -b 0x01000000 WNS54.ram; load -r -v -b 0x01d00000 zImage; go 0x01d00000

Build NS65-uboot:
=================
make rd88f5182_NAS2_TINY_config
make
