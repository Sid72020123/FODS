CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = binary_tree
OBJS = binary_tree.o queue.o stack.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

binary_tree.o: binary_tree.c queue.h stack.h
	$(CC) $(CFLAGS) -c binary_tree.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f $(TARGET) $(OBJS)