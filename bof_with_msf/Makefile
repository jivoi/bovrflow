CC=gcc
CFLAGS=-m32 -std=c99 -Wall -fno-stack-protector -z execstack	# for x64
#CFLAGS=-std=c99 -Wall -fno-stack-protector -z execstack

all: tcp_server

tcp_server: tcp_server.o
	$(CC) $(CFLAGS) -o $@ $^

tcp_server.o: tcp_server.c

clean:
	rm tcp_server.o tcp_server
