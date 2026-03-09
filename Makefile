CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
TARGET = program
SRCDIR = src
INCDIR = include

all: $(TARGET)

$(TARGET): $(SRCDIR)/main.c $(SRCDIR)/abonent.c
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCDIR)/main.c $(SRCDIR)/abonent.c

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
