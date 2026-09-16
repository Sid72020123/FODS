CC = gcc
CFLAGS = -Wall -Wextra -MMD -MP -g

SOURCES = $(wildcard *.c)
PROGRAMS = $(SOURCES:.c=)

all: $(PROGRAMS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(SOURCES:.c=.d)

clean:
	rm -f *.o *.d *.out

.PHONY: all clean