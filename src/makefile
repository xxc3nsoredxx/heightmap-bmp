OBJS = hm-bmp.o bmp.o
CC = gcc
LFLAGS = -pedantic -Wall -Wextra -std=c99 -g
CFLAGS = $(LFLAGS) -c

hm-bmp : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o hm-bmp

hm-bmp.o : hm-bmp.c bmp.h
	$(CC) $(CFLAGS) hm-bmp.c

bmp.o : bmp.c bmp.h
	$(CC) $(CFLAGS) bmp.c

all: hm-bmp
