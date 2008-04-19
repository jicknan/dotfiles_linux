# This shell script is run before Openbox launches.
# Environment variables set here are passed to the Openbox session.

# Set a background color
#BG=xsetroot
#test -z $BG || $BG -solid "#303030"

# D-bus
if which dbus-launch &>/dev/null && test -z "$DBUS_SESSION_BUS_ADDRESS"; then
       eval `dbus-launch --sh-syntax --exit-with-session`
fi

# Make GTK apps look and behave how they were set up in the gnome config tools
if which gnome-settings-daemon &>/dev/null; then
  gnome-settings-daemon &
fi

# Preload stuff for KDE apps
if which start_kdeinit &>/dev/null; then
  LD_BIND_NOW=true start_kdeinit --new-startup +kcminit_startup &
fi

# Programs that will run after Openbox has started
