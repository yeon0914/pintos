CC=gcc
CFLAGS=-g -Wall
TARGET=testlib

OBJS=bitmap.o debug.o hash.o hex_dump.o list.o main.o bitmapcommand.o hashcommand.o listcommand.o
SRCS=bitmap.c debug.c hash.c hex_dump.c list.c main.c bitmapcommand.c hashcommand.c listcommand.o

$(TARGET): $(OBJS) bitmap.h debug.h hash.h hex_dump.h list.h round.h limits.h main.h bitmapcommand.h hashcommand.h listcommand.h
	$(CC) -o $@ $(OBJS)

clean:
	rm -f *.o
	rm -f $(TARGET)

run:
	./$(TARGET)
