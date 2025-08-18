#include <stdio.h>

#include "JSON.h"

static char * readFile(const char * bfFile)
{
    char * contents;
    int length;
    FILE * file;

    file = fopen(bfFile, "rb");

    if (file)
    {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        
        contents = (char*) malloc(sizeof(char) * length);

        fseek(file, 0, SEEK_SET);
        fread(contents, 1, length, file);

        fclose(file);
    }
    else 
    {
        fprintf(stderr, "Couldn't open file %s\n", bfFile);
        contents = NULL;
    }

    return contents;
}