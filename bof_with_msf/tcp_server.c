/*
 * A stupidly simple vulnerable TCP Server
 */
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <unistd.h>

#define BUFFER_SIZE 1024
#define HEADER_SIZE 4


void vuln_read(int cli_fd) {
  char buffer[BUFFER_SIZE];

  // read 4 bytes to get how many bytes to read
  // assuming that incoming header is in little endian
  int to_read;
  read(cli_fd, &to_read, HEADER_SIZE);
  printf("Will read %d bytes\n", to_read);

  int read_bytes = read(cli_fd, buffer, to_read);
  printf("Read: %d bytes\n", read_bytes);
  printf("Incoming message: %s\n", buffer);
}

int main (int argc, char **argv){
  if (argc < 2) {
    printf("Usage: %s [port]\n", argv[0]);
    exit(1);
  }

  int port, sock_fd, cli_fd;
  socklen_t cli_len;
  struct sockaddr_in serv_addr, cli_addr;

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    printf("Error opening a socket\n");
    exit(1);
  }
  
  port = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);

  if (bind(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("Error on bind()\n");
    exit(1);
  }

  listen(sock_fd, 1);
  cli_len = sizeof(cli_addr);
  cli_fd = accept(sock_fd, (struct sockaddr *) &cli_addr, &cli_len);
  if (cli_fd < 0) {
    printf("Error on accept()\n");
    exit(1);
  }

  vuln_read(cli_fd);

  char message[] = "Hello there!\n";
  write(cli_fd, message, strlen(message));

  close(cli_fd);
  close(sock_fd);

  return 0;
}

