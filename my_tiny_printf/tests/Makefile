all: test

test: test.c ../libprintf_NetBSD.a
	gcc -W -Wall -Werror -ansi -pedantic test.c -o test -lprintf_NetBSD -L..

clean:
	rm -f test

distclean:
	rm -f test