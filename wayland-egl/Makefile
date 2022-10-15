CC=gcc
TARGET=wayland-egl
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
LDFLAGS=-lwayland-client

$(TARGET): $(SRCS)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

.PHONY: clean
