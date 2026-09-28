CC = gcc
CFLAGS = -Wall -Wextra -MMD -MP -g

SOURCES = $(wildcard *.c)
PROGRAMS = $(SOURCES:.c=)

all: $(PROGRAMS)

avl_tree: avl_tree.o headers/queue.o headers/stack.o
	$(CC) $(CFLAGS) $^ -o $@.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(SOURCES:.c=.d)

clean:
	rm -f *.o *.d *.out

.PHONY: all clean