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
#include "router.h"

struct Server server_Constructor(int domain, int port, int service, int protocol, int backlog, u_long interface, void (*launch)(struct Server *server)) {
    struct Server server;

    server.domain = domain;
    server.service = service;
    server.port = port;
    server.protocol = protocol;
    server.backlog = backlog;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    server.socket = socket(domain, service, protocol);
    if (server.socket < 0) {
        perror("Failed to initialize socket");
        exit(EXIT_FAILURE);
    }

    if (bind(server.socket, (struct sockaddr*)&server.address, sizeof(server.address)) < 0) {
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server.socket, server.backlog) < 0) {
        perror("Failed to start listening");
        exit(EXIT_FAILURE);
    }

    server.launch = launch;
    return server;
}

void launch(struct Server *server) {
    char buffer[BUFFER_SIZE];
    HttpRequest req;

    router_init();

    /*
     * [변경] 로그 출력 위치 이동
     * 이전: while(1) 내부에서 매 요청마다 "Listening on port..." 출력
     * 이후: while(1) 전에 한 번만 출력
     * 이유: 서버 시작 시 한 번만 알리면 충분하며, 매 요청마다 출력하면
     *       로그가 과도하게 쌓여 디버깅 시 중요한 정보를 찾기 어려움
     */
    printf("Server started on port %d\n", server->port);

    while (1) {
        int addrlen = sizeof(server->address);

        /*
         * [변경] accept() 에러 처리 추가
         * 이전: 에러 처리 없이 바로 read() 호출
         * 이후: new_socket < 0 시 에러 출력 후 continue
         * 이유: accept() 실패 시 잘못된 소켓(-1)으로 read/write 하면
         *       undefined behavior 발생. 에러 로그 후 다음 연결 대기
         */
        int new_socket = accept(server->socket, (struct sockaddr*)&server->address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Failed to accept connection");
            continue;
        }

        ssize_t bytesRead = read(new_socket, buffer, BUFFER_SIZE - 1);
        if (bytesRead >= 0) {
            buffer[bytesRead] = '\0';
            printf("--- Request ---\n%s\n", buffer);

            if (parse_request(buffer, &req) == 0) {
                printf("Method: %s, Path: %s\n", req.method, req.path);
                router_handle(new_socket, &req);
            } else {
                const char *error_html = "<html><body><h1>400 Bad Request</h1></body></html>";
                send_response(new_socket, 400, "Bad Request", error_html);
            }
        } else {
            /*
             * [변경] perror()에서 \n 제거
             * 이전: perror("Error reading buffer...\n");
             * 이후: perror("Error reading buffer");
             * 이유: perror()는 내부적으로 줄바꿈을 추가함.
             *       \n을 명시하면 빈 줄이 하나 더 출력되어 로그 형식이 깨짐
             */
            perror("Error reading buffer");
        }

        close(new_socket);
    }
}

/*
 * [변경] send_response() 함수 시그니처 변경
 * 이전: void send_response(int socket, const char *body)
 * 이후: void send_response(int socket, int status_code, const char *status_text, const char *body)
 * 이유: 이전에는 항상 "200 OK"만 반환했음. 400, 404, 500 등 다양한
 *       HTTP 상태 코드를 반환해야 하므로 매개변수로 받도록 변경
 */
void send_response(int socket, int status_code, const char *status_text, const char *body) {
    char header[512];

    /*
     * [변경] int → size_t
     * 이전: int body_len = strlen(body);
     * 이후: size_t body_len = strlen(body);
     * 이유: strlen()의 반환 타입은 size_t (unsigned).
     *       int로 받으면 매우 큰 문자열에서 오버플로우 가능성 있음.
     *       타입 일치로 컴파일러 경고도 방지
     */
    size_t body_len = strlen(body);

    /*
     * [변경] sprintf → snprintf
     * 이전: sprintf(header, "HTTP/1.1 200 OK\r\n"...);
     * 이후: snprintf(header, sizeof(header), "HTTP/1.1 %d %s\r\n"...);
     * 이유: sprintf()는 버퍼 크기를 체크하지 않아 오버플로우 위험.
     *       snprintf()는 최대 크기를 지정하여 버퍼 초과 시 잘라냄.
     *       보안 취약점(CWE-120: Buffer Overflow) 방지
     */
    snprintf(header, sizeof(header),
            "HTTP/1.1 %d %s\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: %zu\r\n"
            "Connection: close\r\n"
            "\r\n",
            status_code, status_text, body_len);

    /*
     * [변경] write() 반환값 체크 추가
     * 이전: write(socket, header, strlen(header)); (반환값 무시)
     * 이후: 반환값을 확인하고 실패 시 경고 출력
     * 이유: write()가 요청한 바이트 수보다 적게 쓸 수 있음(부분 전송).
     *       네트워크 문제나 클라이언트 연결 끊김 시 -1 반환.
     *       에러 무시하면 불완전한 응답이 전송되어 클라이언트 오류 발생
     */
    ssize_t header_written = write(socket, header, strlen(header));
    if (header_written < 0) {
        perror("Failed to write header");
        return;
    }

    ssize_t body_written = write(socket, body, body_len);
    if (body_written < 0) {
        perror("Failed to write body");
        return;
    }
}
