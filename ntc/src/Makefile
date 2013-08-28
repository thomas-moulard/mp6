include ../../Makefile.rules

OBJS = main.o ntc_extern.o io.o
NTC = ntc

all: ${NTC}

${NTC}: ${OBJS}
	${CC} ${LDLAGS} ${OBJS} -lpthread -o $@ && mv $@ ..

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o *~ \#*\#

distclean:
	rm -f *.o *~ \#*\# ../${NTC}

TAGS:
	emacs-etags *.c *.h

depends:
	gcc -M *.c > '.depends'

include .depends