
SHELL = /bin/sh
CC=gcc
CFLAGS= -Wall -g -ansi -pedantic -Werror
MAIN= fw
OBJS = $(MAIN).o

.PHONY: all test clean


all: $(MAIN)


clean:
	rm -f $(OBJS) *~

test: 
	./fw ./test/*

$(MAIN): $(MAIN).o fw_ds.o fw_read.o fw_vector.o
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) fw_ds.o fw_read.o fw_vector.o

fw.o: fw.c
	$(CC) -c $(CFLAGS) fw.c

fw_ds.o: fw_ds.c fw_ds.h
	$(CC) -c $(CFLAGS) fw_ds.c

fw_read.o: fw_read.c fw_read.h
	$(CC) -c $(CFLAGS) fw_read.c

fw_vector.o: fw_vector.c fw_vector.h
	$(CC) -c $(CFLAGS) fw_vector.c

