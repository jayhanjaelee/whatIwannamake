# pong

[Coding Pong in C from Scratch | Drawing to a Window | Ep. 1](https://youtu.be/m_jDyqcvaQU?si=tbskrHTm8dnU8l0G)

## Makefile

### 1. dylib의 install name을 @rpath 기반으로 변경 (프로젝트 루트 디렉토리에 존재하는 라이브러리 사용하기 위함)

`install_name_tool -id @rpath/libSDL2-2.0.0.dylib lib/libSDL2-2.0.0.dylib`

### 2. 링크 시 -rpath로 실제 검색 경로 지정 (Makefile에서)

`-rpath @executable_path/../lib`
