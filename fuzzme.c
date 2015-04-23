/*
gcc -o fuzzme -fno-stack-protector fuzzme.c
*/

#include <stdio.h>
#include <string.h>
int main(int argc, char** argv)
{
bdcode(argv[1]);
return 0;
}
int bdcode(char *bdinput)
{
char stuff[200];
strcpy(stuff, bdinput);
printf("You passed the following data to fuzzme: %s\n",stuff);
return 0;
}
