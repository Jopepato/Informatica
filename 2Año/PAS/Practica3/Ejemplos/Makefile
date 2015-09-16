.PHONY: clean dist

CC = gcc
CFLAGS = -Wall -g
INCLUDES = #-I.
LFLAGS = #-L.
LIBS = -lrt #-lpthread

MAIN = ejemplo-getopt ejemplo-getoptlong ejemplo-infousuario ejemplo-getenv \
	ejemplo-syslog ejemplo-fork ejemplo-fork-exec ejemplo-fork-wait \
	ejemplo-signal ejemplo-signal-fork ejemplo-mq ejemplo-msg \
	servidor cliente

all:    $(MAIN)
	@echo  Terminado

%:	%.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

ejemplo-mq:	ejemplo-mq.c
		$(CC) $(CFLAGS) $(INCLUDES) $< -o $@ $(LIBS)

servidor:	servidor.c common.h
		$(CC) $(CFLAGS) $(INCLUDES) $< -o $@ $(LIBS)

cliente:	cliente.c common.h
		$(CC) $(CFLAGS) $(INCLUDES) $< -o $@ $(LIBS) 

clean:
	$(RM) *.o *~ $(MAIN)

dist: 
	tar zcvf pas-practica3-ejemplos.tar.gz *.c *.h Makefile
