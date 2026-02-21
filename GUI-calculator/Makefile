CC = clang
CFLAGS = -Wno-unused-command-line-argument \
				 -Wno-gnu-folding-constant \
				 -I/usr/local/include \
				 -Iinclude \
				 `pkg-config --libs sdl3 sdl3-ttf`

LDFLAGS = `pkg-config --libs sdl3 sdl3-ttf`

SRC_DIR = src
BUILD_DIR = build
OBJS_DIR = objs

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/$(OBJS_DIR)/%.o, $(SRCS))

TARGET = $(BUILD_DIR)/app

all: setup $(TARGET) run

setup:
	@mkdir -p $(BUILD_DIR)/$(OBJS_DIR)

$(BUILD_DIR)/$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MD -c -o $@ $^

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

run:
	$(TARGET)

.PHONY: clean

clean:
	@rm -f $(TARGET)
	@rm -r $(OBJS)

print:
	@echo $(SRCS)
	@echo $(OBJS)

