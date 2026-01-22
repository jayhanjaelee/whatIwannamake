/**
 * @file router.h
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-01-22
 */

#ifndef ROUTER_H
#define ROUTER_H

#define MAX_PATH_LENGTH 256
#define MAX_METHOD_LENGTH 16

// HTTP 요청 정보
typedef struct {
    char method[MAX_METHOD_LENGTH];
    char path[MAX_PATH_LENGTH];
} HttpRequest;

// 라우트 구조체
typedef struct {
    const char *path;
    const char *view;
} Route;

// HTTP 요청 파싱
int parse_request(const char *buffer, HttpRequest *req);

// 라우트 매칭 및 실행
void router_handle(int socket, HttpRequest *req);

// 라우트 등록
void router_add_route(const char *path, const char *view);

// 기본 라우트 초기화
void router_init(void);

#endif /* ROUTER_H */
