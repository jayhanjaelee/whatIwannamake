/**
 * @file server.h
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-01-19 21:00
 */

#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

#define BUFFER_SIZE 16000

struct Server {
    int domain;
    int port;
    int service;
    int protocol;
    int backlog;
    u_long interface;

    int socket;
    struct sockaddr_in address;

    // server->launch(), server 구조체의 함수포인터 launch;  method 느낌
    void (*launch)(struct Server *server);
};

struct Server server_Constructor(int domain, int port, int service, int protocol, int backlog, u_long interface, void (*launch)(struct Server *server));
void launch(struct Server *server);
void send_response(int socket, const char *body);

#endif /* SERVER_H */

