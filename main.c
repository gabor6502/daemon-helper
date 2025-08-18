#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <curl/curl.h>

#include <assert.h>

#include "http/Response.h"
#include "json/JSON.h"

size_t writeChunk(void * data, size_t size, size_t bytes_in_block, void * userData);

int main()
{
    CURL * curl;
    CURLcode code;

    curl = curl_easy_init(); 
    if (!curl)
    {
        fprintf(stderr, "Couln't init curl");
        exit(EXIT_FAILURE);
    }

    Response * resp = createResponse();

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeChunk);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) resp);

    // test getting sunrise and sunset times for Winnipeg
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.sunrise-sunset.org/json?lat=49.8951&lng=-97.1384&tzid=America/Winnipeg");
    //curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com"); // will send hella chunks!

    code = curl_easy_perform(curl);

    if (code != CURLE_OK)
    {
        fprintf(stderr, "An error occured: %s\n", curl_easy_strerror(code));
        exit(EXIT_FAILURE);
    }
    
    printf("%s\n", resp->string);

    destroyResponse(resp);
    curl_easy_cleanup(curl);

    return 0;
}

size_t writeChunk(void * data_block_in, size_t size, size_t bytes_in_block, void * data_target)
{
    Response * resp = (Response *) data_target; // data_target will be a Response struct since we set that before running api calls
    size_t real_size = size * bytes_in_block; // official libcurl documentation recommends/enforces this 

    int ret_code = appendChunk(resp, real_size, data_block_in);

    if (ret_code == REPONSE_REALLOCATION_FAILURE)
    {
        return CURL_WRITEFUNC_ERROR; // will signal to libcurl that function failed
    }

    return real_size;
}
