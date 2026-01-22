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
/*
 * [변경] 함수 시그니처 확장
 * 이전: void send_response(int socket, const char *body);
 * 이후: status_code, status_text 매개변수 추가
 * 이유: HTTP 상태 코드(200, 400, 404, 500 등)를 유연하게 지정 가능
 */
void send_response(int socket, int status_code, const char *status_text, const char *body);

#endif /* SERVER_H */

