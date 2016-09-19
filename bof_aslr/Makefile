CC=gcc
#CFLAGS=-m32 -std=c99 -Wall -fno-stack-protector	# for x64
CFLAGS=-std=c99 -Wall -fno-stack-protector -z execstack

all: bof exec

bof: bof.o
	$(CC) $(CFLAGS) -o $@ $^
	sudo chown 0:0 $@
	sudo chmod u+s $@

bof.o: bof.c

exec: exec.o
	ld -melf_i386 -o $@ $^

exec.o: exec.nasm
	nasm -f elf32 -o $@ $^

clean:
	rm bof.o bof exec exec.o
