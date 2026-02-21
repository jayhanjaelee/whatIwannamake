CC := clang
CFLAGS := -Wall -g -O0 -Iinclude
LDFLAGS = -Llib -lSDL2 -rpath @executable_path/../lib
LDFLAGS += -framework CoreVideo -framework Cocoa -framework IOKit -framework OpenGL -framework CoreFoundation

BUILDDIR := build
OBJSDIR := $(BUILDDIR)/objs
SRCDIR := src

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJSDIR)/%.o,$(SRCS))

TARGET := $(BUILDDIR)/pong

all: $(TARGET) run

setup:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(OBJSDIR)

$(OBJSDIR)/%.o: $(SRCDIR)/%.c | setup
	bear -- $(CC) $(CFLAGS) -c -o $@ $^

$(TARGET): $(OBJS) | setup
	$(CC) $(LDFLAGS) -o $@ $^

run: $(TARGET)
	@$(TARGET)

.PHONY: clean

print:
	@echo $(OBJS)

clean:
	@rm -rf $(BUILDDIR)
