#include <stdlib.h>
#include <stdio.h>

#include <curl/curl.h>

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

    // test getting sunrise and sunset times for Winnipeg
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.sunrise-sunset.org/json?lat=49.8951&lng=-97.1384");

    code = curl_easy_perform(curl);

    if (code != CURLE_OK)
    {
        fprintf(stderr, "An error occured: %s\n", curl_easy_strerror(code));
        exit(EXIT_FAILURE);
    }
    
    curl_easy_cleanup(curl);

    return 0;
}