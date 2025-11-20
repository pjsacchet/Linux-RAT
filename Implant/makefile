CC = gcc -static

CFLAGS = -Wall -g

TARGET = ../Out/linuxRAT

SOURCES = Main.c File.c Dir.c Disconnect.c DGA.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)