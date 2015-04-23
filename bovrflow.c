/* This program contains an intentional vulnerability for learning purposes.
gcc -o bovrflow -fno-stack-protector bovrflow.c
Linux uses Address Space Layout Randomization (ASLR) by default
ldd bovrflow

turn off
echo 0 > /proc/sys/kernel/randomize_va_space
*/
#include <stdio.h>
#include <string.h>
int main()
{
char lstring[10];
/* ask for the user to enter a long string */
printf("Enter a long string:");
/* scanf is known to be susceptible to buffer overflow when %s
conversion is used*/
scanf("%s", lstring);
/*Print out the string that was typed*/
printf("You entered: %s\n",lstring);
return 0;
}
