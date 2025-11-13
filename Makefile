# Makefile for Supermarket Management System

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = supermarket
SRC = supermarket.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) products.txt

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
