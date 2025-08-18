#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <curl/curl.h>

typedef struct RESPONSE
{
    char * resp_string;
    size_t resp_size;
} Response;

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

    Response resp;
    resp.resp_string = (char *) malloc(sizeof(char)); // one byte for now, just to init it to something
    resp.resp_size = 0;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeChunk);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &resp);

    // test getting sunrise and sunset times for Winnipeg
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.sunrise-sunset.org/json?lat=49.8951&lng=-97.1384");
    //curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com"); // will send hella chunks!


    code = curl_easy_perform(curl);

    if (code != CURLE_OK)
    {
        fprintf(stderr, "An error occured: %s\n", curl_easy_strerror(code));
        exit(EXIT_FAILURE);
    }
    
    printf("%s\n", resp.resp_string);

    free(resp.resp_string);

    curl_easy_cleanup(curl);

    return 0;
}

size_t writeChunk(void * data_block_in, size_t size, size_t bytes_in_block, void * data_target)
{
    Response * resp = (Response *) data_target; // data_target will be a Response struct since we set that before running api calls
    size_t real_size = size * bytes_in_block; // official libcurl documentation recommends/enforces this 
    char * new_chars = (char *) realloc(resp->resp_string, real_size + resp->resp_size + 1); // reallocate with existing + new chunk + null terminator

    if (new_chars == NULL)
    {
        return CURL_WRITEFUNC_ERROR; // will signal to libcurl that function failed
    }

    resp->resp_string = new_chars;
    memcpy(&resp->resp_string[resp->resp_size], data_block_in, real_size);

    resp->resp_size += real_size;
    resp->resp_string[resp->resp_size] = '\0';

    return real_size;
}
