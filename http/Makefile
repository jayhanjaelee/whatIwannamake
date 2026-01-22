# HTTP Server Makefile
CC = clang
CFLAGS = -Wall -Wextra -g

# Directories
BIN_DIR = bin

# Include paths
INCLUDES = -Isrc/server -Isrc/controllers

# Source files
SRCS = src/main.c \
       src/server/server.c \
       src/controllers/router.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output
TARGET = $(BIN_DIR)/server

# Default target
all: $(TARGET)

# Create bin directory if not exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(BIN_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS)
	rm -rf $(BIN_DIR)

# Run server
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
