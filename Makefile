CC=gcc
CFLAGS=-Wall

SOURCES = main.c
TARGET = main

INCLUDE = -I/home/elan/dev/libs/libcurl/curl/include
LINKLIB = -L/home/elan/dev/libs/libcurl/curl/lib
LDFLAGS = -lcurl

RESPONSE_H = ./http/Response.h
RESPONSE_C = ./http/Response.c

JSON_H = ./json/JSON.h
JSON_C = ./json/JSON.c

STACK_H = ./json/stack/Stack.h
STACK_C = ./json/stack/Stack.c
STACK_O = Stack.o

#Request.o - add in when working
OBJS = Response.o JSON.o Stack.o

# to turn off debugging for release:
#-dNDEBUG

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDE) $(OBJS) -o $(TARGET) $(LINKLIB) $(LDFLAGS)

#Request.o: ./http/Request.h ./http/Request.c
#	$(CC) $(CFLAGS) -c ./http/Request.c

Response.o: $(RESPONSE_H) $(RESPONSE_C)
	$(CC) $(CFLAGS) -c $(RESPONSE_C)

JSON.o : $(JSON_H) $(JSON_C) 
	$(CC) $(CFLAGS) -c $(JSON_C)

Stack.o: $(STACK_H) $(STACK_C)
	$(CC) $(CFLAGS) -c $(STACK_C)

clean:
	rm -rf $(TARGET)
	rm -rf $(OBJS)