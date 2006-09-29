#~/.bash_profile
if [ "$PROFILED" != "1" ]; then
    echo "profiling..."
    [ -f /etc/profile ] && . /etc/profile
#    export PROFILED="1"
fi
