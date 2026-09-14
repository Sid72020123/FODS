CC = gcc
CFLAGS = -Wall -Wextra -g -MMD -MP

SOURCES = $(wildcard *.c)
PROGRAMS = $(SOURCES:.c=)

all: $(PROGRAMS)

binary_tree: binary_tree.o queue.o stack.o
	$(CC) $(CFLAGS) $^ -o $@.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(SOURCES:.c=.d)

clean:
	rm -f *.o *.d *.out

.PHONY: all clean