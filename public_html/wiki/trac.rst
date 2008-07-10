=================
Trac on Archlinux
=================
the notes for me
================

:Copyright: Copyright 2008 Jick Nan.
:Author: Jick Nan <jick.nan 在 gmail.com>
:Create Date: Mon 07 Jul 2008 03:43:07 PM CST

Installation
------------

Requirements
~~~~~~~~~~~~

- For ArchLinux::

  $ sudo pacman -S python-genshi python-pysqlite
  $ sudo yaourt -S mod_wsgi
  /*
  To install mod_wsgi, add the followsing line in
  /etc/httpd/conf/httpd.conf file:

  LoadModule wsgi_module modules/mod_wsgi.so

  WSGIScriptAlias /trac /usr/local/trac/mysite/apache/mysite.wsgi

  <Directory /usr/local/trac/mysite/apache>
  WSGIApplicationGroup %{GLOBAL}
  Order deny,allow
  Allow from all
  </Directory>

  and restart/reload Apache.
  */

- Options

  * python-babel for localization support
  * docutils for WikiRestructuredText.
  * Pygments for syntax highlighting, also SilverCity and/or Enscript may
    still be used. 
  * pytz to get a complete list of time zones, otherwise Trac will fall back
    on a shorter list from an internal time zone implementation. 


Installing Trac
~~~~~~~~~~~~~~~

::
  # (Option) I18N generating
  $ python ./setup.py compile_catalog -f
  $ python ./setup.py install


Creating a Project Environment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

$ trac-admin /path/to/myproject initenv
# chown -R apache.apache /path/to/myproject 





Resources
---------
- `reStructuredText Support in Trac`__
- `Trac Installation Guide for 0.12dev`__

__ http://trac.edgewall.org/wiki/WikiRestructuredText
__ http://trac.edgewall.org/wiki/0.12/TracInstall
