#ifndef __REQUEST_H__
#define __REQUEST_H__

typedef struct REQUEST
{
    char * category; // like is it email, weather, etc.
    char * url; // with query params

    // will likely need more functionality for request bodies

} Request;

Request * create();
void destroy(Request * req);

#endif