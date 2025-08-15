CC=gcc
CFLAGS=-Wall

SOURCES = main.c
TARGET = main

INCLUDE = -I/home/elan/dev/libs/libcurl/curl/include
LINKLIB = -L/home/elan/dev/libs/libcurl/curl/lib
LDFLAGS = -lcurl

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDE) -o $(TARGET) $(LINKLIB) $(LDFLAGS)
clean:
	rm -rf $(TARGET)