CC=gcc
#CFLAGS=-m32 -std=c99 -Wall		# for x86_64
CFLAGS=-std=c99 -Wall

all: pass_change

pass_change: pass_change.o
	$(CC) $(CFLAGS) -o $@ $^
	sudo chown 0:0 $@
	sudo chmod u+s $@

pass_change.o: pass_change.c

clean:
	rm pass_change.o pass_change
