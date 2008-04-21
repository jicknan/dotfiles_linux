#!/usr/bin/env python

import sys
try:
 	import pygtk
  	pygtk.require("2.0")
except:
  	pass
try:
	import gtk
  	import gtk.glade
except:
	sys.exit(1)

class HellowWorldGTK:
	"""This is an Hello World GTK application"""

	def __init__(self):
		
		#Set the Glade file
		self.gladefile = "pyhelloworld.glade"  
	        self.wTree = gtk.glade.XML(self.gladefile) 
		
		#Create our dictionay and connect it
		dic = { "on_btnHelloWorld_clicked" : self.btnHelloWorld_clicked,
			"on_MainWindow_destroy" : gtk.main_quit }
		self.wTree.signal_autoconnect(dic)

	def btnHelloWorld_clicked(self, widget):
		print "Hello World!"


if __name__ == "__main__":
	hwg = HellowWorldGTK()
	gtk.main()
