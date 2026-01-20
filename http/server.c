/**
 * @file server.c
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-01-19 21:01
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

#include "server.h"

struct Server server_Constructor(int domain, int port, int service, int protocol, int backlog, u_long interface, void (*launch)(struct Server *server)) {
    struct Server server;

    server.domain = domain;
    server.service = service;
    server.port = port;
    server.protocol = protocol;
    server.backlog = backlog;

    server.address.sin_family = domain;
    // htonl, htons – convert values between host and network byte order
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    // return -1 if error occured, otherwise the return value is a descriptor referencing the socket.
    server.socket = socket(domain, service, protocol);
    if (server.socket < 0) {
        // handle error.
        perror("Failed to initialize/connect to socket...\n");
        exit(EXIT_FAILURE);
    }

    if (bind(server.socket, (struct sockaddr*)&server.address, sizeof(server.address)) < 0) {
        perror("Failed to bind socket...\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server.socket, server.backlog) < 0) {
        perror("Failed to start listening...\n");
        exit(EXIT_FAILURE);
    }

    server.launch = launch;
    return server;
}

void launch(struct Server *server) {
    char buffer[BUFFER_SIZE];
    while (1) {
        printf("Listening on %d:%u\n", server->port, server->address.sin_addr.s_addr );
        int addrlen = sizeof(server->address);
        int new_socket = accept(server->socket, (struct sockaddr*)&server->address, (socklen_t*)&addrlen);
        ssize_t bytesRead = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (bytesRead >= 0) {
            buffer[bytesRead] = '\0';  // Null terminate the string
            puts(buffer);
        } else {
            perror("Error reading buffer...\n");
        }

        const char *html_body =
        "<!DOCTYPE html>\r\n"
        "<html>\r\n"
        "<head><title>Testing</title></head>\r\n"
        "<body><h1>Hello, World!</h1></body>\r\n"
        "</html>\r\n";
        send_response(server->socket, html_body);

        close(server->socket);
    }
}

void send_response(int socket, const char *body) {
    char header[512];
    int body_len = strlen(body);

    // 1. 헤더 생성 (Content-Length를 자동으로 계산해서 넣어줍니다)
    sprintf(header,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: %d\r\n"
            "Connection: close\r\n"
            "\r\n",
            body_len);

    // 2. 헤더 전송
    write(socket, header, strlen(header));

    // 3. 바디 전송
    write(socket, body, body_len);
}

