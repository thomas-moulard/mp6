include ../../Makefile.rules

OBJS = fifo.o ../src/io.o
FIFO = fifo

all: ${FIFO}

${FIFO}: ${OBJS}
	${CC} ${LDLAGS} ${OBJS} -lpthread -o $@

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o *~ \#*\#

distclean:
	rm -f *.o *~ \#*\#

TAGS:
	emacs-etags *.c *.h

depends:
	gcc -M *.c > '.depends'

include .depends