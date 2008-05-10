RSTOPTS=--time --link-stylesheet --stylesheet=style.css

SOURCES=$(wildcard *.rst)
HTML=$(foreach file,$(SOURCES),$(basename $(file)).html)

all: html

%.html: %.rst
	rst2html.py $(RSTOPTS) $^ > $@

html: $(HTML)

clean:
	rm -f $(HTML)

install:
	upload2ftp
