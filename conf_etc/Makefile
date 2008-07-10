# Makefile for install my conf files into my host

DESTDIR = /etc
PWDDIR = $(shell /bin/pwd)
RM=/bin/rm -ir
LN=/bin/ln -siv
ECHO=/bin/echo
TOUCH=`which touch`
INSTALL=`which install`

DIRS := 

FILES := X11/xorg.conf
#FILES += DIR_COLORS
#FILES += fonts/local.conf
FILES += httpd/conf
FILES += logrotate.d
FILES += pacman.d
#FILES += profile.d/*
#FILES += samba/smb.conf
FILES += ssh/ssh_config
FILES += ssh/sshd_config
#FILES += tor
FILES += uucp
FILES += xinetd.d
#FILES += DIR_COLORS
FILES += cpufreqd.conf
FILES += hosts
FILES += hosts.allow
FILES += hosts.deny
#FILES += inetd.conf
FILES += logrotate.conf
FILES += makepkg.conf
FILES += modprobe.conf
FILES += pacman.conf
#FILES += profile
#FILES +=  qemu-ifup
FILES += rc.local
#FILES += termcap
FILES += vsftpd.conf
FILES += xinetd.conf

# Out of control:
# inittab
# fstab
# rc.conf

all: env
	@(for _FILE in ${FILES}; do \
	    [ -e ${DESTDIR}/$$(dirname $${_FILE}) ] || \
		mkdir -p ${DESTDIR}/$$(dirname $${_FILE}); \
		ls -l ${DESTDIR}/$${_FILE}; \
	    if [ "${JICK_HOST}x" != "x" -a -f $${_FILE}_${JICK_HOST} ]; then \
	            ${LN} ${PWDDIR}/$${_FILE}_${JICK_HOST} ${DESTDIR}/$${_FILE} || exit 1; \
	    else \
	        ${LN} ${PWDDIR}/$${_FILE} ${DESTDIR}/$${_FILE} || exit 1; \
	    fi \
	done)

del: 
	@(for _FILE in ${FILES}; do \
	    echo "${DESTDIR}/$${_FILE}"; \
	    if [ -e ${DESTDIR}/$${_FILE} ]; then \
		ls -l ${DESTDIR}/$${_FILE}; \
	    $(RM) ${DESTDIR}/$${_FILE} || exit 2; \
	    fi \
	done)

echo:
	@echo "@=${@}"
	@echo "JICK_HOST=${JICK_HOST}"
	@echo "----- DIRS -----"
	@(for _DIR in ${DIRS}; do \
		/bin/echo "$${_DIR}"; \
	done)
	@echo "----- FILES -----"
	@(for _FILE in ${FILES}; do \
		/bin/echo "$${_FILE} || $$(dirname $${_FILE})"; \
	done)

env:
	@(if [ "${JICK_HOST}x" = "x" ]; then \
	    echo "Please set JICK_HOST pls."; \
	    exit 1; \
	else \
	    echo ">> working on $${JICK_HOST}..."; \
	fi)

$(DIRS): env
	make -C $@ all

$(FILES): env
	echo ${FILE}
	if [ "${JICK_HOST}x" != "x" -a -f $@_${JICK_HOST} ]; then \
	    ${LN} ${PWDDIR}/${@}_${JICK_HOST} ${DESTDIR}/${@} || exit 1; \
	else \
	    ${LN} ${PWDDIR}/${@} ${DESTDIR}/${@} || exit 1; \
	fi \

.PHONY: $(DIRS) $(FILES)
