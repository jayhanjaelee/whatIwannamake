/**
 * @file router.c
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-01-22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "router.h"

#define MAX_ROUTES 32
#define MAX_FILE_SIZE 65536
#define VIEWS_DIR "src/views/"
#define STATIC_DIR "src/static/"

static Route routes[MAX_ROUTES];
static int route_count = 0;

// 파일 읽기
static char *read_file(const char *filepath, long *out_size) {
    FILE *file = fopen(filepath, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (size <= 0 || size > MAX_FILE_SIZE) {
        fclose(file);
        return NULL;
    }

    char *content = malloc(size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(content, 1, size, file);
    content[read_size] = '\0';
    fclose(file);

    if (out_size) *out_size = read_size;
    return content;
}

// Content-Type 결정
static const char *get_content_type(const char *path) {
    const char *ext = strrchr(path, '.');
    if (!ext) return "application/octet-stream";

    if (strcmp(ext, ".css") == 0) return "text/css";
    if (strcmp(ext, ".js") == 0) return "application/javascript";
    if (strcmp(ext, ".html") == 0) return "text/html";
    if (strcmp(ext, ".png") == 0) return "image/png";
    if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) return "image/jpeg";
    if (strcmp(ext, ".gif") == 0) return "image/gif";
    if (strcmp(ext, ".svg") == 0) return "image/svg+xml";

    return "application/octet-stream";
}

// HTTP 응답 전송
static void send_response(int socket, int status_code, const char *status_text,
                          const char *content_type, const char *body, long body_len) {
    char header[512];

    sprintf(header,
            "HTTP/1.1 %d %s\r\n"
            "Content-Type: %s; charset=UTF-8\r\n"
            "Content-Length: %ld\r\n"
            "Connection: close\r\n"
            "\r\n",
            status_code, status_text, content_type, body_len);

    write(socket, header, strlen(header));
    write(socket, body, body_len);
}

// view 파일 응답
static void send_view(int socket, int status_code, const char *status_text, const char *view) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", VIEWS_DIR, view);

    long size;
    char *content = read_file(filepath, &size);
    if (content) {
        send_response(socket, status_code, status_text, "text/html", content, size);
        free(content);
    } else {
        const char *error = "<html><body><h1>500 Internal Server Error</h1></body></html>";
        send_response(socket, 500, "Internal Server Error", "text/html", error, strlen(error));
    }
}

// 정적 파일 응답
static int serve_static(int socket, const char *path) {
    // /static/ 접두사 확인
    if (strncmp(path, "/static/", 8) != 0) return 0;

    // 경로 조작 방지
    if (strstr(path, "..") != NULL) {
        const char *error = "<html><body><h1>403 Forbidden</h1></body></html>";
        send_response(socket, 403, "Forbidden", "text/html", error, strlen(error));
        return 1;
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "src%s", path);  // src 접두사 추가

    long size;
    char *content = read_file(filepath, &size);
    if (content) {
        send_response(socket, 200, "OK", get_content_type(path), content, size);
        free(content);
    } else {
        const char *error = "<html><body><h1>404 Not Found</h1></body></html>";
        send_response(socket, 404, "Not Found", "text/html", error, strlen(error));
    }
    return 1;
}

// ================== Router API ==================

int parse_request(const char *buffer, HttpRequest *req) {
    memset(req, 0, sizeof(HttpRequest));
    if (sscanf(buffer, "%15s %255s", req->method, req->path) != 2) {
        return -1;
    }
    return 0;
}

void router_add_route(const char *path, const char *view) {
    if (route_count >= MAX_ROUTES) {
        fprintf(stderr, "Max routes exceeded\n");
        return;
    }
    routes[route_count].path = path;
    routes[route_count].view = view;
    route_count++;
}

void router_init(void) {
    route_count = 0;
    router_add_route("/", "index.html");
    router_add_route("/about", "about.html");
    router_add_route("/posts", "posts.html");
}

void router_handle(int socket, HttpRequest *req) {
    // 정적 파일 먼저 처리
    if (serve_static(socket, req->path)) return;

    // 라우트 매칭
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].path, req->path) == 0) {
            send_view(socket, 200, "OK", routes[i].view);
            return;
        }
    }
    send_view(socket, 404, "Not Found", "404.html");
}
