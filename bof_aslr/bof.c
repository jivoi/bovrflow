#include    <stdio.h>
#include    <stdlib.h>
#include    <assert.h>
#include	<string.h>


void vuln (const char* arg){
	char buffer[100];
	strcpy(buffer, arg);
	printf("Hello %s\n", buffer);
	printf("[+] buffer @ %p\n", buffer);
}		/* -----  end of function vuln  ----- */

int main (int argc, char **argv){
	
	if (argc != 2) {
		printf("Usage: %s <buffer>\n", argv[0]);
		exit(1);
	}
	vuln(argv[1]);
		return 0;
}

