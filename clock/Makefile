CC = clang
CFLAGS = -Iinclude
LDFLAGS = -Llib -lraylib -framework CoreVideo -framework Cocoa -framework IOKit -framework GLUT -framework OpenGL

SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/app

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

all: setup $(TARGET) run

setup:
	@mkdir -p $(BUILDDIR)

$(OBJS): $(SRCS)
	bear -- $(CC) $(CFLAGS) -c -o $@ $^

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

run:
	$(TARGET)

print:
	@echo "SRCS:" $(SRCS)
	@echo "OBJS:" $(OBJS)
	@echo "TARGET:" $(TARGET)
