#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>

#include "Response.h"

Response * createResponse()
{
    Response * new = (Response *) malloc(sizeof(Response));
    assert(new != NULL);

    new->string = (char *) malloc(sizeof(char)); // init to one byte due to future reallocations and memory copying
    assert(new->string != NULL);

    new->size = 0;

    return new;
}

void destroyResponse(Response * resp)
{
    assert(resp != NULL);
    assert(resp->string != NULL);

    if (resp != NULL)
    {   
        if (resp->string != NULL)
        {
            free(resp->string);
        }

        free(resp);
    }
}

int appendChunk(Response * resp, size_t chunk_size, void * data_block_in)
{
    assert(resp != NULL);
    assert(resp->string != NULL);
    assert(data_block_in != NULL);
    assert(chunk_size > 0);

    char * new_chars = (char *) realloc(resp->string, chunk_size + resp->size + 1); // reallocate with existing + new chunk + null terminator
    
    assert(new_chars != NULL);
    if (new_chars == NULL)
    {
        return REPONSE_REALLOCATION_FAILURE;
    }

    resp->string = new_chars;
    memcpy(&resp->string[resp->size], data_block_in, chunk_size);

    resp->size += chunk_size;
    resp->string[resp->size] = '\0';

    return RESPONSE_REALLOCATION_OK;
}