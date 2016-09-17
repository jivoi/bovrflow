#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <fcntl.h>
#include    <unistd.h>

struct data {
    char buffer[100];
    char datafile[20];
};

int main (int argc, char **argv){
    struct data data;

    strcpy(data.datafile, "/var/notes");

    if (argc < 2) {
        printf("Usage: %s <buffer>\n", argv[0]);
        exit(1);
    }

    strcpy(data.buffer, argv[1]);

    printf("[DEBUG] data.buffer @ %p: \'%s\'\n", data.buffer, data.buffer);
    printf("[DEBUG] data.datafile @ %p: \'%s\'\n", data.datafile, data.datafile);

    int fd;
    fd = open(data.datafile, O_WRONLY| O_APPEND);
    printf("[DEBUG] fd @ %p: %d\n", &fd, fd);

    if (write(fd, data.buffer, strlen(data.buffer)) == -1) {
        fprintf(stderr, "in main() - no write\n");
        exit(1);
    }
    if (close(fd) == -1) {
        fprintf(stderr, "in main() - no close\n");
        exit(1);
    }
        return 0;
}