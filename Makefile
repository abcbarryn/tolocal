# Makefile for advent

OBJS	= tolocal.o

CC	= gcc
CFLAGS	= -O2

all:	tolocal

tolocal:	$(OBJS)
	$(CC) -o tolocal $(OBJS) -liconv
	strip tolocal

install:	tolocal
	cp tolocal /usr/local/bin
	chmod a+x /usr/local/bin/tolocal
	cp tolocal.1 /usr/local/share/man/man1

.o:
	$(CC) -i -c $@.c

clean:	
	@rm -rf *.o *.s *.bak *.dat core tolocal
