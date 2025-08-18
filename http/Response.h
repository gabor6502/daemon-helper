#ifndef __RESPONSE_H__
#define __RESPONSE_H__

typedef size_t; 

typedef struct RESPONSE
{
    char * string;
    size_t size;
} Response;

Response * create();
void destroy(Response * res);

#endif