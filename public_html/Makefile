
TOPDIR = $(PWD)

LIBDIRS = assets/inc

#SUBDIRS :=
#SUBDIRS += 

OBJ = index link note search whatsnew bookmarklet

.PHONY:all
all: $(OBJ)

bookmarklet: bookmarklet_main.html
	@./tools/generator.sh $@ "Bookmarklets used by Jick Nan" sidebartop

index: index_main.html
	@./tools/generator.sh $@ "Jick Nan" sidebartop

link: link_main.html
	@./tools/generator.sh $@ "Links for Jick Nan" sidebartop nosidebar

note: note_main.html
	@./tools/generator.sh $@ "Design Notes of the site" sidebartop

search: search_main.html
	@./tools/generator.sh $@ "Simple All-in-One Search" sidebartop nosidebar

whatsnew: whatsnew_main.html
	@./tools/generator.sh $@ "What's new on the site?" sidebartop

dirs: 
	@for i in ${SUBDIRS} ;  do                                                \
	echo "-----------------------------------------------------------------"; \
	echo -e "\033[;34m                         $$i                 \033[;0m"; \
	echo "-----------------------------------------------------------------"; \
	make -C $$i || exit 1 ;                                                   \
	done

.PHONY:clean install
clean:
	#for i in ${SUBDIRS} ; do make -C $$i clean || exit 1 ; done
	#for i in ${LIBDIRS} ; do make -C $$i clean || exit 1 ; done
	rm -f *.bak *~

install:
	upload2ftp
