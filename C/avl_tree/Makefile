CC = gcc
CFLAGS = -Wall -Wextra -MMD -MP -g

PROGRAM = avl_tree

SOURCES = avl_tree.c \
          headers/queue.c \
          headers/stack.c

OBJECTS = $(SOURCES:.c=.o)
DEPS = $(OBJECTS:.o=.d)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJECTS) $(DEPS) $(PROGRAM)

.PHONY: all clean