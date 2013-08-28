include ../Makefile.rules

all:
	cd src && make all

debug:
	cd src && make debug

check:
	cd tests && ./moulinette.sh

clean:
	cd src && make clean
	cd tests && make clean
	rm -f *.o \#*\# *~

distclean:
	cd src && make distclean
	cd tests && make distclean
	rm -f *.o \#*\# *~ Makefile.rules *.a *.so