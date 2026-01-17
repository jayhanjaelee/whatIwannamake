CC = cc
CFLAGS = -Wall -O0

SRCS = hj_time.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Library module compiled: $@"

clean:
	rm -f *.o *.d

.PHONY: all clean
