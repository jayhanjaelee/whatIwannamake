CC = cc
INCLUDE = -Iinclude

ifeq ($(DEBUG), 1)
    CFLAGS = -Wall -Wextra -g -O0 $(INCLUDE)
else
    CFLAGS = -Wall -Wextra -O2 $(INCLUDE)
endif

# 시스템 PATH에서 ctags를 찾되, 절대 경로를 우선시하고 싶을 때
CTAGS := /opt/homebrew/Cellar/universal-ctags/p6.2.20260111.0/bin/ctags

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/main

# 1. 하위 폴더의 모든 .c 파일을 재귀적으로 찾음
SRCS = $(shell find $(SRC_DIR) -name "*.c")

# 2. 소스 경로(src/dir/file.c)를 오브젝트 경로(obj/dir/file.o)로 변환
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

all: tags $(TARGET)

# 3. .o 파일을 만들 때 해당 하위 폴더가 없으면 자동으로 생성
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -MD

$(TARGET) : $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: tags clean check
tags:
	@# 쉘의 [ -x 경로 ] 명령으로 실제 실행 가능 여부 체크, 실제 파일이 존재하는 경우에만 실행한다.
	@if [ -x $(CTAGS) ]; then \
		$(CTAGS) -R --exclude='.*' --exclude=obj --exclude=bin .; \
	fi

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) tags

check:
	@echo "--------------------------"
	@echo "Source Files: $(SRCS)"
	@echo "Object Files: $(OBJS)"
	@echo "Include Path: $(INCLUDE)"
	@echo "Target Path:  $(TARGET)"
	@echo "--------------------------"

-include $(DEPS)
