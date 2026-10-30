CC = gcc
CFLAGS = -Wall -Wextra -MMD -MP -g

SOURCES = $(wildcard *.c)
PROGRAMS = $(SOURCES:.c=)

all: $(PROGRAMS)

graph_array: graph_array.o headers/queue.o headers/stack.o
	$(CC) $(CFLAGS) $^ -o $@.out

graph_linked_list: graph_linked_list.o headers/queue.o headers/stack.o
	$(CC) $(CFLAGS) $^ -o $@.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(SOURCES:.c=.d)

clean:
	rm -f *.o *.d *.out

.PHONY: all clean