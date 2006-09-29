#!/bin/sh
#
# /etc/rc.d/rc.S:  System initialization script.
#
# Mostly written by:  Patrick J. Volkerding, <volkerdi@slackware.com>
#

PATH=/sbin:/usr/sbin:/bin:/usr/bin

# Mount /proc right away:
/sbin/mount -v proc /proc -n -t proc

# If 'nohotplug' was given at boot, or rc.hotplug has been turned off
# (and a 2.4.x kernel is running), then shut off hotplugging in the
# kernel now.  Realize that if you turn off hotplugging support that
# you will have to load all the kernel modules that you need yourself
# (possibly in /etc/rc.d/rc.modules, which does not promise to list
# all of them), and make any additional device nodes that you need in
# the /dev directory.
if [ -w /proc/sys/kernel/hotplug ]; then
  # Kernel command line option 'nohotplug' given, so we will shut off
  # hotplugging even if it is not a good idea.  Sometimes it *is* a
  # good idea, especially when you're trying to figure out which
  # kernel module is crashing the machine and needs to be added to
  # your /etc/modprobe.d/blacklist (2.6+ kernels) and/or your
  # /etc/hotplug/blacklist (2.4.x kernels).
  if grep -wq nohotplug /proc/cmdline ; then
    echo "/dev/null" > /proc/sys/kernel/hotplug
  elif [ ! -x /etc/rc.d/rc.hotplug ]; then
    # Ignore /etc/rc.d/rc.hotplug on kernels newer than 2.4.x:
    if [ ! "$(uname -r | cut -f 1,2 -d .)" = "2.4" ]; then
      # We must be running a 2.4.x kernel, so turn off hotplug:
      echo "/dev/null" > /proc/sys/kernel/hotplug
    fi
  fi
fi

# Start devfsd if necessary.  On newer kernels, udev should be used instead.
if [ -x /etc/rc.d/rc.devfsd ]; then
  /etc/rc.d/rc.devfsd start
fi

# Mount sysfs next, if the kernel supports it:
if [ -d /sys ]; then
  if cat /proc/filesystems | grep -wq sysfs ; then
    if ! cat /proc/mounts | grep -wq sysfs ; then
      /sbin/mount -v sysfs /sys -n -t sysfs
    fi
  fi
fi

# Enable swapping:
/sbin/swapon -a

# Test to see if the root partition is read-only, like it ought to be.
READWRITE=no
if touch /fsrwtestfile 2>/dev/null; then
  rm -f /fsrwtestfile
  READWRITE=yes
else
  echo "Testing root filesystem status:  read-only filesystem"
fi

# See if a forced filesystem check was requested at shutdown:
if [ -r /etc/forcefsck ]; then
  FORCEFSCK="-f"
fi

# Check the root filesystem:
if [ ! $READWRITE = yes ]; then
  RETVAL=0
  if [ ! -r /etc/fastboot ]; then
    echo "Checking root filesystem:"
    /sbin/fsck $FORCEFSCK -C -a /
    RETVAL=$?
  fi
  # An error code of 2 or higher will require a reboot.
  if [ $RETVAL -ge 2 ]; then
    # An error code equal to or greater than 4 means that some errors
    # could not be corrected.  This requires manual attention, so we
    # offer a chance to try to fix the problem in single-user mode:
    if [ $RETVAL -ge 4 ]; then
      echo
      echo "***********************************************************"
      echo "*** An error occurred during the root filesystem check. ***"
      echo "*** You will now be given a chance to log into the      ***"
      echo "*** system in single-user mode to fix the problem.      ***"
      echo "***                                                     ***"
      echo "*** If you are using the ext2 filesystem, running       ***"
      echo "*** 'e2fsck -v -y <partition>' might help.              ***"
      echo "***********************************************************"
      echo
      echo "Once you exit the single-user shell, the system will reboot."
      echo
      PS1="(Repair filesystem) \#"; export PS1
      sulogin
    else # With an error code of 2 or 3, reboot the machine automatically:
      echo
      echo "***********************************"
      echo "*** The filesystem was changed. ***"
      echo "*** The system will now reboot. ***"
      echo "***********************************"
      echo
    fi
    echo "Unmounting file systems."
    /sbin/umount -a -r
    /sbin/mount -n -o remount,ro /
    echo "Rebooting system."
    sleep 2
    reboot -f
  fi
  # Remount the root filesystem in read-write mode
  echo "Remounting root device with read-write enabled."
  /sbin/mount -w -v -n -o remount /
  if [ $? -gt 0 ] ; then
    echo
    echo "Attempt to remount root device as read-write failed!  This is going to"
    echo "cause serious problems."
    echo 
    echo "If you're using the UMSDOS filesystem, you **MUST** mount the root partition"
    echo "read-write!  You can make sure the root filesystem is getting mounted "
    echo "read-write with the 'rw' flag to Loadlin:"
    echo
    echo "loadlin vmlinuz root=/dev/hda1 rw   (replace /dev/hda1 with your root device)"
    echo
    echo "Normal bootdisks can be made to mount a system read-write with the rdev command:"
    echo
    echo "rdev -R /dev/fd0 0"
    echo
    echo "You can also get into your system by using a boot disk with a command like this"
    echo "on the LILO prompt line:  (change the root partition name as needed)"
    echo 
    echo "LILO: mount root=/dev/hda1 rw"
    echo
    echo "Please press ENTER to continue, then reboot and use one of the above methods to"
    echo -n "get into your machine and start looking for the problem. " 
    read junk; 
  fi
else
  echo "Testing root filesystem status:  read-write filesystem"
  if cat /etc/fstab | grep ' / ' | grep -wq umsdos ; then
    ROOTTYPE="umsdos"
  fi
  if [ ! "$ROOTTYPE" = "umsdos" ]; then # no warn for UMSDOS
    echo
    echo "*** ERROR: Root partition has already been mounted read-write. Cannot check!"
    echo
    echo "For filesystem checking to work properly, your system must initially mount"
    echo "the root partition as read only. Please modify your kernel with 'rdev' so that"
    echo "it does this. If you're booting with LILO, add a line:"
    echo
    echo "   read-only"
    echo
    echo "to the Linux section in your /etc/lilo.conf and type 'lilo' to reinstall it."
    echo
    echo "If you boot from a kernel on a floppy disk, put it in the drive and type:"
    echo "   rdev -R /dev/fd0 1"
    echo
    echo "If you boot from a bootdisk, or with Loadlin, you can add the 'ro' flag."
    echo
    echo "This will fix the problem *AND* eliminate this annoying message. :^)"
    echo
    echo -n "Press ENTER to continue. "
    read junk;
  fi
fi # Done checking root filesystem

# Any /etc/mtab that exists here is old, so we delete it to start over:
/bin/rm -f /etc/mtab*
# Remounting the / partition will initialize the new /etc/mtab:
/sbin/mount -w -o remount /

# Fix /etc/mtab to list sys and proc if they were not yet entered in
# /etc/mtab because / was still mounted read-only:
if [ -d /proc/sys ]; then
  /sbin/mount -f proc /proc -t proc
fi
if [ -d /sys/bus ]; then
  /sbin/mount -f sysfs /sys -t sysfs
fi

# Initialize udev to manage /dev entries and hotplugging for 2.6.x kernels.
# You may turn off udev by making the /etc/rc.d/rc.udev file non-executable,
# but in the 2.6.x+ kernels udev has taken over the job of hotplug (finding
# hardware and loading the kernel modules for it, as well as creating device
# nodes in /dev).  Realize that if you turn off udev that you will have to
# load all the kernel modules that you need yourself (possibly in
# /etc/rc.d/rc.modules, which does not promise to list all of them), and
# make any additional device nodes that you need in the /dev directory.
# Even USB and IEEE1394 devices will need to have the modules loaded by
# hand if udev is not used with a 2.6 kernel.  So use it.  :-)
if cat /proc/mounts | grep -wq sysfs && cat /proc/filesystems | grep -wq tmpfs ; then
  if ! grep -wq nohotplug /proc/cmdline ; then
    if [ -x /etc/rc.d/rc.udev ]; then
      /bin/sh /etc/rc.d/rc.udev start
      /bin/sh /lib/udev/udev.count_events.sh
    fi
  fi
fi

# Set the system time from the hardware clock using hwclock --hctosys.
if [ -x /sbin/hwclock ]; then
  # Check for a broken motherboard RTC clock (where ioports for rtc are
  # unknown) to prevent hwclock causing a hang:
  if ! grep -q -w rtc /proc/ioports ; then
    CLOCK_OPT="--directisa"
  fi
  if grep -wq "^UTC" /etc/hardwareclock ; then
    echo "Setting system time from the hardware clock (UTC)."
    /sbin/hwclock $CLOCK_OPT --utc --hctosys
  else
    echo "Setting system time from the hardware clock (localtime)."
    /sbin/hwclock $CLOCK_OPT --localtime --hctosys
  fi
fi

# Configure ISA Plug-and-Play devices:
if [ -r /etc/isapnp.conf ]; then
  if [ -x /sbin/isapnp ]; then
    /sbin/isapnp /etc/isapnp.conf
  fi
fi

# This loads any kernel modules that are needed.  These might be required to
# use your ethernet card, sound card, or other optional hardware.
# Priority is given first to a script named "rc.modules.local", then
# to "rc.modules-$FULL_KERNEL_VERSION", and finally to the plain "rc.modules".
# Note that if /etc/rc.d/rc.modules.local is found, then that will be the ONLY
# rc.modules script the machine will run, so make sure it has everything in
# it that you need.
if [ -x /etc/rc.d/rc.modules.local -a -r /proc/modules ]; then
  echo "Running /etc/rc.d/rc.modules.local:"
  /bin/sh /etc/rc.d/rc.modules.local
elif [ -x /etc/rc.d/rc.modules-$(uname -r) -a -r /proc/modules ]; then
  echo "Running /etc/rc.d/rc.modules-$(uname -r):"
  . /etc/rc.d/rc.modules-$(uname -r)
elif [ -x /etc/rc.d/rc.modules -a -r /proc/modules -a -L /etc/rc.d/rc.modules ]; then
  echo "Running /etc/rc.d/rc.modules -> $(readlink /etc/rc.d/rc.modules):"
  . /etc/rc.d/rc.modules
elif [ -x /etc/rc.d/rc.modules -a -r /proc/modules ]; then
  echo "Running /etc/rc.d/rc.modules:"
  . /etc/rc.d/rc.modules
fi

# Configure runtime kernel parameters:
if [ -x /sbin/sysctl -a -r /etc/sysctl.conf ]; then
  /sbin/sysctl -e -p /etc/sysctl.conf
fi

# Initialize the Logical Volume Manager.
# This won't start unless we find /etc/lvmtab (LVM1) or 
# /etc/lvm/backup/ (LVM2).  This is created by /sbin/vgscan, so to
# use LVM you must run /sbin/vgscan yourself the first time (and
# create some VGs and LVs).
if [ -r /etc/lvmtab -o -d /etc/lvm/backup ]; then
  echo "Initializing LVM (Logical Volume Manager):"
  # Check for device-mapper support.
  if ! cat /proc/devices | grep -wq device-mapper ; then
    # If device-mapper exists as a module, try to load it.
    if [ -r /lib/modules/$(/bin/uname -r)/kernel/drivers/md/dm-mod.ko ]; then
      insmod /lib/modules/$(/bin/uname -r)/kernel/drivers/md/dm-mod.ko
    fi
  fi
  # Scan for new volume groups:
  KERNEL_VERSION=$(/bin/uname -r | /bin/cut -d . -f 1,2)
  if [ "$KERNEL_VERSION" == "2.4" ]; then
    /sbin/vgscan 2> /dev/null
  else
    /sbin/vgscan --ignorelockingfailure 2> /dev/null
  fi
  if [ $? = 0 ]; then
    # Make volume groups available to the kernel.
    # This should also make logical volumes available.
    if [ "$KERNEL_VERSION" == "2.4" ]; then
      /sbin/vgchange -ay
    else
      /sbin/vgchange -ay --ignorelockingfailure
    fi
    # Enable swapping again in case any LVs are used for swap.  Ignore previous error.  :-)
    /sbin/swapon -a
  fi
fi

# Check all the non-root filesystems:
if [ ! -r /etc/fastboot ]; then
  echo "Checking non-root filesystems:"
  /sbin/fsck $FORCEFSCK -C -R -A -a
fi

# Mount usbfs if we're not using hotplug:
if grep -wq usbfs /proc/filesystems; then
  if /bin/grep -wq nohotplug /proc/cmdline || /bin/test ! -x /etc/rc.d/rc.hotplug ; then
    if ! cat /proc/mounts | grep -wq usbfs ; then
      /sbin/mount -v usbfs /proc/bus/usb -t usbfs
    fi
  fi
fi

# Mount non-root file systems in fstab, but not NFS or SMB 
# because TCP/IP is not yet configured, and not proc or sysfs
# because those have already been mounted.  Also check that
# devpts is not already mounted before attempting to mount
# it.  With 2.4.x kernels devpts is mounted from an fstab
# entry while with a 2.6.x or newer kernel udev mounts it.
# We also need to wait a little bit to let USB and other
# hotplugged devices settle (sorry to slow down the boot):
echo "Mounting non-root local filesystems:"
sleep 3
if /bin/grep -wq devpts /proc/mounts ; then
  /sbin/mount -a -v -t nonfs,nosmbfs,nocifs,noproc,nosysfs,nodevpts
else
  /sbin/mount -a -v -t nonfs,nosmbfs,nocifs,noproc,nosysfs
fi

# Enable swapping again.  This is needed in case a swapfile is used,
# as it can't be enabled until the filesystem it resides on has been
# mounted read-write.
/sbin/swapon -a

# Clean up temporary files: (jnan)
echo "Clean up temporary files: /tmp"
/bin/rm -rf /tmp/*

# Clean up some temporary files:
( cd /var/log/setup/tmp && rm -rf * )
/bin/rm -f /var/run/utmp /var/run/*pid /etc/nologin /var/run/lpd* \
  /var/run/ppp* /etc/dhcpc/*.pid /etc/forcefsck /etc/fastboot \
  /var/state/saslauthd/saslauthd.pid

# Create /tmp/{.ICE-unix,.X11-unix} if they are not present:
if [ ! -e /tmp/.ICE-unix ]; then
  mkdir -p /tmp/.ICE-unix
  chmod 1777 /tmp/.ICE-unix
fi
if [ ! -e /tmp/.X11-unix ]; then
  mkdir -p /tmp/.X11-unix
  chmod 1777 /tmp/.X11-unix
fi

# Attempt to umount and remove any leftover /initrd:
if [ -d /initrd ]; then
  umount /initrd/proc 2> /dev/null
  /sbin/umount /initrd 2> /dev/null
  rmdir /initrd 2> /dev/null
  blockdev --flushbufs /dev/ram0 2> /dev/null
fi

# Create a fresh utmp file:
touch /var/run/utmp
chown root:utmp /var/run/utmp
chmod 664 /var/run/utmp

if [ "$ROOTTYPE" = "umsdos" ]; then # we need to update any files added in DOS:
  echo "Synchronizing UMSDOS directory structure:"
  echo "  /sbin/umssync -r99 -v- /"
  /sbin/umssync -r99 -v- /
fi

# Setup the /etc/motd to reflect the current kernel level:
# THIS WIPES ANY CHANGES YOU MAKE TO /ETC/MOTD WITH EACH BOOT.
# COMMENT THIS OUT IF YOU WANT TO MAKE A CUSTOM VERSION.
echo "$(/bin/uname -sr)." > /etc/motd

# If there are SystemV init scripts for this runlevel, run them.
if [ -x /etc/rc.d/rc.sysvinit ]; then
  . /etc/rc.d/rc.sysvinit
fi

# Run serial port setup script:
# (CAREFUL! This can make some systems hang if the rc.serial script isn't
# set up correctly. If this happens, you may have to edit the file from a
# boot disk)
#
# . /etc/rc.d/rc.serial

# Carry an entropy pool between reboots to improve randomness.
if [ -f /etc/random-seed ]; then
  echo "Using /etc/random-seed to initialize /dev/urandom."
  cat /etc/random-seed > /dev/urandom
fi
# Use the pool size from /proc, or 512 bytes:
if [ -r /proc/sys/kernel/random/poolsize ]; then
  dd if=/dev/urandom of=/etc/random-seed count=1 bs=$(cat /proc/sys/kernel/random/poolsize) 2> /dev/null
else
  dd if=/dev/urandom of=/etc/random-seed count=1 bs=512 2> /dev/null
fi
chmod 600 /etc/random-seed

