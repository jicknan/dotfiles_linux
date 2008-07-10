import os

os.environ['TRAC_ENV'] = '/home/jick/project/jicknan/public_html/trac'
os.environ['PYTHON_EGG_CACHE'] = '/home/jick/project/jicknan/public_html/trac/eggs'

import trac.web.main
application = trac.web.main.dispatch_request
