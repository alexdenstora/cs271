CC = gcc
CFLAGS = -g -Wall -I.
LDFLAGS =
OBJFILES = main.o parser.o symtable.o error.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~