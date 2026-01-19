/**
 * @file main.c
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-01-19 20:29
 */

#include <stdio.h>
#include "server.h"

int main(void) {
    /**
      1. socket(int domain, int type, int protocol);
      2. bind(int socket, const struct sockaddr *address, socklen_t address_len);
      3. int listen(int socket, int backlog);
      4. accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
      5. connect(int socket, const struct sockaddr *address, socklen_t address_len);
      6. ssize_t send(int socket, const void *buffer, size_t length, int flags);
      7. ssize_t recv(int socket, void *buffer, size_t length, int flags);
      8. int close(int fildes);
      */

    struct Server server = server_Constructor(AF_INET, 8080, SOCK_STREAM, 0, 10, INADDR_ANY, launch);
    server.launch(&server);
    return 0;
}


