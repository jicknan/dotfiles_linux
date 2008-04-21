#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Idea from: http://wanted.eu.org/en/computers/linux/uploading_photos_to_picasaweb
#
# Author: Artyom 'logus' Pervukhin < logus9@gmail.com >
# License: GPLv2
#

import sys, os, cPickle as pickle
try:
    import gdata.service
except ImportError:
    sys.exit('You have to install gdata-python-client: http://code.google.com/p/gdata-python-client/')
try:
    import atom
except ImportError:
    sys.exit('You have to install atom python module')
from optparse import OptionParser
from getpass import getpass

def main():
    usage = """Usage: %prog [options] albumname filename1.jpg filename2.jpg ...

    Uploads jpeg files to Google's Picasa Web Albums service.
    Running for the first time will ask for login/password and save them
    to ~/.google_auth (be sure to check its access rights, password is
    stored as plain text)."""

    parser = OptionParser(usage=usage)
    parser.add_option("-i", "--init", action="store_true", dest="initrun",
            help="call in init mode, asking login/password")
    parser.add_option("-l", "--list", action="store_true", dest="listalbums",
            help="list user's albums")
    parser.add_option("-p", "--public", action="store_true", dest="bepublic",
            help="create album as public (private by default)")
    parser.add_option("-n", "--new", action="store_true", dest="benew",
            help="create new album (even if the album w/same name exists)")
    parser.set_defaults(initrun=False, listalbums=False,
            bepublic=False, benew=False)

    (options, args) = parser.parse_args()
    if len(args) == 0 and not options.listalbums:
        parser.print_help()
        sys.exit()
    #print options
    #print args
    
    if options.listalbums == False and len(args) < 2:
        parser.error("No album name and/or files specified!")

    username, password = auth(options.initrun)
    gds = login(username, password)
    albums, albumlist = getalbums(gds, username)

    if options.listalbums:
        for i in albumlist: print "%s\t%s" % (i[0], i[1])
        if len(args) < 2:
            sys.exit() # if no album name and/or files, just exit (if user wants only list)

    albumname = args[0].decode('utf-8')
    files = args[1:]
    if options.bepublic:
        rights = 'public'
    else:
        rights = 'private'

    feedurl = None # initial value
    if options.benew == False:
        feedurl = findalbum(albumname, albums, username)
    else:
        feedurl = createnewalbum(albumname, rights, gds, username)

    if not feedurl:
        feedurl = createnewalbum(albumname, rights, gds, username)
    
    postfiles(files, feedurl, gds)

    sys.exit()



def auth(isinitrun=False):
    """Read authentication data from user input and store it to file.

    Read authentication data from user and store it to file;
    if file exists and user auth is not forced, read data from
    file and return them.
    """
    def getfilename(name):
        if os.name == 'posix': return os.path.join(os.path.expanduser('~'), name)
        if os.name == 'nt': return os.path.join(os.environ.get('USERPROFILE'), name)
        return name # if os.name not 'posix' or 'nt'

    authfile = getfilename('.google_auth')

    def getsaved():
        try:
            return open (os.path.expanduser(authfile), 'r')
        except:
            raise # pass exception to the top call
            return None

    def askandwrite():
        username = str(raw_input('Login (without suffix @gmail.com): '))
        password = getpass('Password (would not be displayed): ')
        try:
            authdata = open (os.path.expanduser(authfile), 'w')
            pickle.dump((username, password), authdata)
            authdata.close()
            os.chmod(authfile, 384) # 0600
        except IOError, (errno, strerror):
            print "I/O error(%s): %s" % (errno, strerror)
        return (username, password)

    if isinitrun == True:
        username, password = askandwrite()
    else:
        try:
            authdata = getsaved()
            username, password = pickle.load(authdata)
            authdata.close()
        except IOError, (errno, strerror):
            print "I/O error(%s): %s" % (errno, strerror)
            username, password = askandwrite()
        except:
            print "Unexpected error:", sys.exc_info()[0]
            username, password = askandwrite()
    return (username, password)

def login(username, password):
    """Perform login procedure to picasaweb.google.com.
    """
    gds = gdata.service.GDataService()
    gds.email = username
    gds.password = password
    gds.service = 'lh2' # where to get the list of all possible values?
    try:
        gds.ProgrammaticLogin()
    except gdata.service.CaptchaRequired:
        sys.exit('Required Captcha')
    except gdata.service.BadAuthentication:
        sys.exit('Bad Authentication')
    except gdata_client.Error:
        sys.exit('Login Error')
    return gds

def getalbums(gds, username):
    """Retrieve list of user's albums.

    Get user's list of albums and return them - both in user-friendly
    mode, and like feed object.
    """
    try:
        albums = gds.GetFeed(
                'http://picasaweb.google.com/data/feed/api/user/'
                + username
                + '?kind=album&access=all'
                )
    except:
        sys.exit('Error while receiving albums list: ' + sys.exc_info()[0])
    else:
        # extract rights and titles in human-readable form
        albums_index = [(i.rights.text, i.title.text) for i in albums.entry]
    return (albums, albums_index)

def findalbum(albumname, albums, username):
    """Search if the albums with specified name exists.

    Get desired album name and user's albums feed object and try to
    find if there's an album with this name. If album exits, return
    its feed url for posting.
    """
    album = None
    for i in albums.entry: # searching through albums, if there's one with the name specified
        if i.title.text == albumname:
            album = i # get entry instance with the corresponded name
            break # stop iterating
    if not album:
        return None
    else:
        return album.link[0].href # album feed url

def createnewalbum(albumname, rights, gds, username):
    """Create new album with specified name and rights.

    Create new album with specified name, rights and return its feed url for posting.
    """
    print 'Photos will be inserted in a newly-created album', albumname, 'with rights', rights # debug
    # prepare metadata
    gdata_entry = gdata.GDataEntry()
    gdata_entry.title = atom.Title(text=albumname)
    # create new albums as private
    gdata_entry.rights = atom.Rights(text=rights) # standard atom rights
    # extended rights definition in google namespace
    ext_rights = atom.ExtensionElement(
		    tag='access',
		    namespace='http://schemas.google.com/photos/2007')
    ext_rights.text = rights # setting the extended rights
    gdata_entry.extension_elements.append(ext_rights)
    # listing categories of gdata_entry (binding to picasa service)
    gdata_entry.category.append(atom.Category(
            scheme = gdata.GDATA_NAMESPACE + '#kind',
            term = 'http://schemas.google.com/photos/2007#album'
            ))
    # create new album entry by submitting gdata object
    try:
        album = gds.Post(
                gdata_entry,
                'http://picasaweb.google.com/data/feed/api/user/' + username
                )
    except:
        sys.exit('Error while creating new album: ' + sys.exc_info()[0])
    # Note: here we have `album` as gdata.GDataEntry object
    return album.GetFeedLink().href # return album feed url


def postfiles(files, feedlink, gds):
    """Post files to album via specified feed url.
    """
    media = gdata.MediaSource() # object for storing file's binary data
    for file in files:
        try:
            print 'Posting file', file,
            media.setFile(file, 'image/jpeg')
            posted_photo = gds.Post(
                    None, # used for metadata ?
                    feedlink, # album feed url
                    media_source = media, # object with file's data
                    extra_headers = { 'Slug:': file } # HTTP-header for setting filename
                    )
        except gdata.service.RequestError:
            print 'Error sending file'
        except:
            print 'Undexpected error:', sys.exc_info()[0]
        else:
            print 'OK'


if __name__ == "__main__":
    main()
