u-boot for NS65:
================
set bootargs console=ttyS0,115200 root=/dev/ram; set ethaddr 00:c0:02:00:c0:66; set serverip 172.21.6.2; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage; tftpboot 0x1100000 romdisk; bootm 0x400000

set bootargs console=ttyS0,115200 root=/dev/ram; set ethaddr 00:c0:02:00:c0:66; set serverip 172.21.6.70; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage; tftpboot 0x1100000 romdisk; bootm 0x400000

set ethaddr 00:c0:02:00:c0:66; set serverip 172.21.7.20; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage;tftpboot 0x1100000 romdisk; bootm 0x400000

set ethaddr 00:c0:02:00:c0:66; set serverip 172.21.6.5; set ipaddr 172.21.6.77; tftpboot 0x400000 uImage; bootm 0x400000

set ethaddr 00:c0:02:00:c0:66; set serverip 172.21.6.26; set ipaddr 172.21.6.77; bubt; reset

set bootargs console=ttyS0,115200 root=/dev/ram; set ethaddr 00:c0:02:00:c0:66; set serverip 192.168.0.1; set ipaddr 192.168.0.100; tftpboot 0x400000 uImage; tftpboot 0x1100000 romdisk; bootm 0x400000

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
