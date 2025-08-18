#ifndef __STACK_H__
#define __STACK_H__

typedef struct NODE
{
    void * cargo;
    struct NODE * below; // the node below this node in the stack
} Node;

typedef struct STACK
{
    Node * top;
} Stack;

Stack * createStack();
void destroyStack(Stack * stack);

void push(void * data, Stack * stack);
void * pop(Stack * stack);

#endif