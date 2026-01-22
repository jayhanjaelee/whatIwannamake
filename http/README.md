# HTTP Server in C

C로 작성된 간단한 HTTP 서버입니다.

## 빌드 및 실행

```bash
make        # 빌드
make run    # 빌드 후 실행
make clean  # 정리
```

## 프로젝트 구조

```
http/
├── src/
│   ├── main.c              # 진입점
│   ├── server/             # 서버 코어
│   │   ├── server.c
│   │   └── server.h
│   ├── controllers/        # 라우팅 및 요청 처리
│   │   ├── router.c
│   │   └── router.h
│   ├── views/              # HTML 템플릿
│   │   ├── index.html
│   │   ├── about.html
│   │   ├── posts.html
│   │   └── 404.html
│   └── static/             # 정적 파일
│       └── css/
│           └── style.css
├── bin/                    # 실행 파일 (빌드 후 생성)
├── Makefile
└── README.md
```

---

## 요청 처리 흐름

### 전체 흐름도

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│   Client    │────▶│   Server    │────▶│   Router    │────▶│    View     │
│  (Browser)  │◀────│  (socket)   │◀────│  (handler)  │◀────│   (HTML)    │
└─────────────┘     └─────────────┘     └─────────────┘     └─────────────┘
```

---

### 1단계: 서버 초기화 (main.c → server.c)

```
main()
   │
   ▼
server_Constructor()
   │
   ├── 1. Server 구조체 생성
   │
   ├── 2. socket() ─────────── 통신 채널 생성
   │
   ├── 3. bind() ───────────── 포트에 소켓 연결
   │
   ├── 4. listen() ─────────── 연결 대기 상태
   │
   └── 5. Server 반환
```

**비유**: 새 가게를 열고 전화기를 개통하여 손님을 받을 준비를 하는 과정

---

### 2단계: 요청 대기 및 수신 (server.c - launch)

```
launch()
   │
   ├── router_init() ────────── 라우트 테이블 초기화
   │
   └── while(1) ─────────────── 무한 루프 (서버 계속 실행)
          │
          ├── accept() ──────── 클라이언트 연결 수락 (블로킹)
          │      │
          │      └── new_socket 반환 (클라이언트 전용 소켓)
          │
          ├── read() ────────── HTTP 요청 읽기
          │      │
          │      └── "GET /about HTTP/1.1\r\n..."
          │
          ├── parse_request() ─ 요청 파싱
          │      │
          │      └── method: "GET", path: "/about"
          │
          ├── router_handle() ─ 라우팅 처리
          │
          └── close() ───────── 연결 종료
```

**비유**: 가게 직원이 손님을 맞이하고, 주문을 듣고, 상품을 전달하는 과정

---

### 3단계: 라우팅 (router.c)

```
router_handle(socket, req)
   │
   ├── /static/* 경로인가? ─── Yes ──▶ serve_static()
   │         │                              │
   │         No                             └── 파일 읽어서 응답
   │         │
   │         ▼
   ├── 라우트 테이블 검색
   │   ┌─────────────────────────────┐
   │   │  path        │  view        │
   │   ├─────────────────────────────┤
   │   │  "/"         │ "index.html" │
   │   │  "/about"    │ "about.html" │
   │   │  "/posts"    │ "posts.html" │
   │   └─────────────────────────────┘
   │         │
   │   매칭 발견? ─── Yes ──▶ send_view(200, view)
   │         │
   │         No
   │         │
   │         ▼
   └── send_view(404, "404.html")
```

**비유**: 메뉴판에서 주문한 음식을 찾아 제공하는 과정

---

### 4단계: 응답 전송 (server.c - send_response)

```
send_response(socket, status_code, status_text, body)
   │
   ├── 1. HTTP 헤더 생성
   │      ┌────────────────────────────────┐
   │      │ HTTP/1.1 200 OK                │
   │      │ Content-Type: text/html        │
   │      │ Content-Length: 1234           │
   │      │ Connection: close              │
   │      │                                │
   │      └────────────────────────────────┘
   │
   ├── 2. write(header) ────── 헤더 전송
   │
   └── 3. write(body) ──────── 본문 전송
```

**비유**: 택배 송장(헤더)을 작성하고, 상품(본문)을 포장하여 발송

---

### 전체 시퀀스 다이어그램

```
  Client                Server                Router               View
    │                     │                     │                    │
    │ ──── TCP 연결 ────▶ │                     │                    │
    │                     │                     │                    │
    │ ── HTTP Request ──▶ │                     │                    │
    │    "GET /about"     │                     │                    │
    │                     │                     │                    │
    │                     │ ── parse_request ─▶ │                    │
    │                     │                     │                    │
    │                     │ ── router_handle ─▶ │                    │
    │                     │                     │                    │
    │                     │                     │ ── read_file ────▶ │
    │                     │                     │                    │
    │                     │                     │ ◀── about.html ─── │
    │                     │                     │                    │
    │                     │ ◀── HTML content ── │                    │
    │                     │                     │                    │
    │ ◀─ HTTP Response ── │                     │                    │
    │    "200 OK + HTML"  │                     │                    │
    │                     │                     │                    │
    │ ◀── 연결 종료 ───── │                     │                    │
```

---

## 라우트 추가 방법

`src/controllers/router.c`의 `router_init()` 함수에 추가:

```c
void router_init(void) {
    route_count = 0;
    router_add_route("/", "index.html");
    router_add_route("/about", "about.html");
    router_add_route("/posts", "posts.html");
    router_add_route("/contact", "contact.html");  // 새 라우트 추가
}
```

그 후 `src/views/contact.html` 파일 생성.

---

## 주요 함수 설명

| 함수 | 파일 | 역할 |
|------|------|------|
| `server_Constructor` | server.c | 서버 소켓 생성 및 초기화 |
| `launch` | server.c | 클라이언트 요청 대기 및 처리 루프 |
| `send_response` | server.c | HTTP 응답 전송 |
| `router_init` | router.c | 라우트 테이블 초기화 |
| `router_handle` | router.c | 요청 URL에 맞는 핸들러 실행 |
| `parse_request` | router.c | HTTP 요청 문자열 파싱 |
