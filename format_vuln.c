#include <stdio.h>

// $ cc format_vuln.c -o format_vuln
// $ ./format_vuln %d
// -7912
// ./format_vuln %d.%d.%d.%d.%d.%d.%s

void f(char *str) {
    char *secret_data = "My Awesome Key";
    printf(str);
}

int main(int argc, char **argv) {
    f(argv[1]);
    return 0;
}