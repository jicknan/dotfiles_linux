#!/bin/sh

# If possible, log events in /var/log/messages:
if [ -f /var/run/syslogd.pid -a -x /usr/bin/logger ]; then
  LOGGER=/usr/bin/logger
else # output to stdout/stderr:
  LOGGER=/bin/cat
fi

echo "Mounting /dev/sda to /mnt/s1mp3" | $LOGGER
mount /dev/sda /mnt/s1mp3 -o iocharset=cp936

echo "Syncing podcasting..." | $LOGGER
rsync -avub -exclude '{LOG,New*}' /data/podcast /mnt/s1mp3

echo "Umounting /mnt/s1mp3..." | $LOGGER
umount /mnt/s1mp3
