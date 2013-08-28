include ../../Makefile.rules

OUT = my_sig_guess
OBJS = main.o

all: ${OUT}

${OUT}: ${OBJS}
	${CC} ${OBJS} -o $@ && mv $@ ..

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *.o *~ \#*\#

distclean:
	rm -f *.o *~ \#*\# ../${OUT}

debug: ${OBJS}
	${CC} ${OBJS} -g -o dbg-${OUT} && mv dbg-${OUT} ..

TAGS:
	emacs-etags *.c *.h

depends:
	gcc -M *.c > '.depends'

include .depends