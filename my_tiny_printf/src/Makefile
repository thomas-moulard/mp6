include ../../Makefile.rules

OBJS = tiny_printf.o

all: ${LIB_TINY_PRINTF}

${LIB_TINY_PRINTF}: ${OBJS}
	ar cr $@ ${OBJS} && mv $@ ..

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o *~ \#*\#

distclean:
	rm -f *.o *~ \#*\# ../${LIB_TINY_PRINTF}

TAGS:
	emacs-etags *.c *.h

depends:
	gcc -M *.c > '.depends'

include .depends