all: my_sig_guess/my_sig_guess ntc/ntc my_tiny_printf/libprintf_NetBSD.a

my_sig_guess/my_sig_guess:
	cd my_sig_guess && make

ntc/ntc:
	cd ntc && make

my_tiny_printf/libprintf_NetBSD.a:
	cd my_tiny_printf && make

clean:
	cd my_sig_guess && make clean
	cd ntc && make clean
	cd my_tiny_printf && make clean

distclean:
	cd my_sig_guess && make distclean
	cd ntc && make distclean
	cd my_tiny_printf && make distclean

dist:
	make distclean
	cd .. && tar -cjf 'moular_t-mp6.tar.bz2' 'moular_t-mp6'