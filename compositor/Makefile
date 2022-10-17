CC=gcc
TARGET=compositor
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
LDFLAGS=-lwayland-server

$(TARGET): $(SRCS)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

.PHONY: clean
