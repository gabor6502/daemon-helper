CC=gcc
CFLAGS=-Wall

SOURCES = main.c
TARGET = main

INCLUDE = -I/home/elan/dev/libs/libcurl/curl/include
LINKLIB = -L/home/elan/dev/libs/libcurl/curl/lib
LDFLAGS = -lcurl

OBJS = Request.o Response.o

all: $(TARGET)

$(TARGET): $(SOURCES) $(OBJS)
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDE) -o $(TARGET) $(LINKLIB) $(LDFLAGS)

Request.o: ./http/Request.h ./http/Request.c
	$(CC) $(CFLAGS) -c ./http/Request.c

Response.o: ./http/Response.h ./http/Response.c
	$(CC) $(CFLAGS) -c ./http/Response.c

clean:
	rm -rf $(TARGET)
	rm -rf $(OBJS)