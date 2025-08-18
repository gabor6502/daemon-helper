#ifndef __JSON_H__
#define __JSON_H__

typedef enum TYPE {NUMBER, STRING, OBJECT, LIST} Type;

typedef struct JSON_NUMBER
{
    char * name;
    int value;

} JsonNumber;

typedef struct JSON_STRING
{
    char * name;
    char * contents;

} JsonString;

typedef struct JSON_OBJ
{   
    char * name;
    union JSON_ELEMENT * elements;
    
} JsonObject;

typedef struct JSON_LIST
{
    char * name;
    union JSON_ELEMENT * array;

} JsonList;

typedef union JSON_ELEMENT
{
    Type t;
    JsonNumber number;
    JsonString string;
    JsonObject object;
    JsonList list; 

} JsonElement;

typedef union JSON
{
    JsonElement * root; // pointer to root of json strcuture
} Json;

Json * createJSON(const char * jsonString);
void destroyJSON(Json * json);

#endif