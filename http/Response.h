#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#define REPONSE_REALLOCATION_FAILURE -1
#define RESPONSE_REALLOCATION_OK 0

typedef struct RESPONSE
{
    char * string;
    size_t size;
} Response;

Response * create();
void destroy(Response * res);

int appendChunk(Response * resp, size_t chunk_size, void * data_block_in);

#endif