// $ gcc vuln_no_nx.c -o vuln_no_prots -fno-stack-protector -no-pie -Wl,-z,norelro -m32 -z execstack
// $ echo 0 > /proc/sys/kernel/randomize_va_space

// pwndbg> checksec
// [*] '/home/pwnbox/DEP/binary/vuln_no_prots'
//     Arch:     i386-32-little
//     RELRO:    No RELRO
//     Stack:    No canary found
//     NX:       NX disabled
//     PIE:      No PIE (0x8048000)
//     RWX:      Has RWX segments

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char totally_secure(char *arg2[])
{
    char buffer[256];
    printf("What is your name?\n");
    strcpy(buffer, arg2[1]);
    printf("Hello: %s!\n", buffer);
}


int main(int argc, char *argv[])
{
 setvbuf(stdin, 0, 2, 0);
 setvbuf(stdout, 0, 2, 0);
 printf("Hello, I'm your friendly & totally secure binary :)!\n");
 totally_secure(argv);
 return 0;
}