CC=gcc
CFLAGS=-Wall

SOURCES = main.c
TARGET = main

INCLUDE = -I/home/elan/dev/libs/libcurl/curl/include
LINKLIB = -L/home/elan/dev/libs/libcurl/curl/lib
LDFLAGS = -lcurl

RESPONSE_H = ./http/Response.h
RESPONSE_C = ./http/Response.c

#Request.o - add in when working
OBJS = Response.o 

# to turn off debugging for release:
#-dNDEBUG

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDE) $(OBJS) -o $(TARGET) $(LINKLIB) $(LDFLAGS)

#Request.o: ./http/Request.h ./http/Request.c
#	$(CC) $(CFLAGS) -c ./http/Request.c

Response.o: $(RESPONSE_H) $(RESPONSE_C)
	$(CC) $(CFLAGS) -c $(RESPONSE_C)

clean:
	rm -rf $(TARGET)
	rm -rf $(OBJS)