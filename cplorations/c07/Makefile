CC = gcc
CFLAGS = -Werror -Wall -I. -g
LDFLAGS = 
OBJFILES = main.o parser.o symtable.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
