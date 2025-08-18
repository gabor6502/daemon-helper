#ifndef __REQUEST_H__
#define __REQUEST_H__

typedef struct REQUEST
{
    char * url; // with query params

    // will likely need more functionality for request bodies

} Request;

Request * create();
void destroy(Request * req);

void addParam(Request * req, char * key, char * value);
void addParamString(Request * req, char * param);

#endif