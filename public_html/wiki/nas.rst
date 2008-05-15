==============================
Network Attached Storage (NAS)
==============================
my notes & thoughts
===================

:Copyright: Copyright 2008 Jick Nan.
:Author: Jick Nan <jick.nan 在 gmail.com>
:Create Date: Mon 12 May 2008 10:05:34 PM CST

Thoughts
--------

如何取得 NAS 上的文件变动？(2008/05/12)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
一边让 Devices 做 NS54 -> NS65 的 backup，一边洗衣服，冒出个想法：
依托 NAS 的存储优势，为公司同事提供一相对稳定的存储空间，一方面也
算是对 NAS 产品做测试。以前也有过此举动，只是后来因为位置调整，
停了下来。

因为公司已经有了一个比较好的电影存储空间，同时 sunny 哥更新电影也很
及时。因此，如果再推出一存储空间，招牌将不是“新”，而是经典与方便。

想到的一个问题是： 针对 NAS 上多人读写的情况，如何将文件的变动
及时获得并广播出来？

- 在获取变动上，可以利用 inotify。NS65 的 linux kernel 2.6.12 已经打过补丁，支持 inotify 了。
- 广播策略上，有如下方式可以考虑：

  - 写 ChangLog，放在相应的 Share Folder 下，可以在 HTTP/FTP 访问时看到。
  - 提供 RSS，推送给订阅者。
  - 提供邮件订阅。

这些都需要注意 1) 方便阅读； 2）不能打扰订阅者，也就是如何应对大量更新。

TODO
----
- castget@NS65: download podcast auto.
