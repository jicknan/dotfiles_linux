=========
Using LVM
=========
Logical Volume Manager
======================

:Copyright: Copyright 2008 Jick Nan.
:Author: Jick Nan <jick.nan 在 gmail.com>
:Create Date: Mon 26 May 2008 06:55:58 PM CST

.. contents::

LVM 可以在不改变硬盘分区表的情况下改变你的分区大小。在你用尽了所有
磁盘空间时，LVM 非常有用，你可以简单的扩充你现在的分区模式，而不会
丢失数据。

LVM Terms
---------
LVM 术语非常重要，基本上理解了 LVM 术语，也就可以玩转 LVM 了。

- physical volume (PV): 普通物理磁盘分区在 LVM 中的名字。

- logical volume (LV): 相当于非 LVM 中的磁盘分区；LV 被视为标准的
  块设备，可以创建文件系统。

- volume group (VG): 这是 LVM 中的最高层抽象。它把一些 LV 和 PV
  集合在一起，作为一个管理单元。

- physical extent (PE): Each physical volume is divided chunks of
  data, known as physical extents, these extents have the same size
  as the logical extents for the volume group. 

- logical extent (LE): Each logical volume is split into chunks of
  data, known as logical extents. The extent size is the same for
  all logical volumes in the volume group. 

The quick list
--------------

Adding a Logical Volume
~~~~~~~~~~~~~~~~~~~~~~~

- backup::

  # tar cvfz backup-home.tar.gz /home

- fdisk, and change the partition system id to 8e (Linux LVM)

- pvcreate (Create Physical Volume)::

  # pvcreate /dev/sdb1
  # pvdisplay

- vgcreate (Create Volume group)::

  # vgcreate vg0 /dev/sdb1
  # vgdisplay

- lvcreate (to assign LV size)::

  # lvcreate -l $(PE) vg0
  # lvdisplay

- mkfs -j (reformat the filesystem)::

  # mkfs.xfs /dev/vg0/lvol0

- fstab (edit to suite your needs)::

  /dev/vg0/lvol0 /home xfs   defaults   0 0

- mount (remount the new volume)::

  # mount /dev/vg0/lvol0 /mnt/tmp

Extending a Logical volume
~~~~~~~~~~~~~~~~~~~~~~~~~~

- backup

- umount

- fdisk, and change the partition system id to 8e (Linux LVM)

- pvcreate (Create Physical Volume)

- vgextend (Extend the Volume Group)

- lvextend (Extend the LV)
- mount
- ext2online (Expand volume to the actual size)
- umount
- e2fsck -f (check the filesystem)
- mount (remount the new volume) 

Removing Logical Volumes
~~~~~~~~~~~~~~~~~~~~~~~~

- backup (do you need data on this volume?)
- umount (umount volume)
- lvremove (remove Logical Volume) 

Usage
-----

- Delete a vg::

  vgchange -a n vg0
  lvremove /dev/vg0/lv0
  vgremove vg0

Resources
--------
- http://fedoranews.org/mediawiki/index.php/Expanding_Linux_Partitions_with_LVM
