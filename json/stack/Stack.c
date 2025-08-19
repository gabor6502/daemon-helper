#include <stdlib.h>
#include <assert.h>

#include "Stack.h"

Stack * createStack()
{
    Stack * stack = (Stack *) malloc(sizeof(Stack));

    assert(stack != NULL);
    if (stack == NULL)
    {
        return NULL;
    }

    stack->top = NULL;

    return stack;
}

void destroyStack(Stack * stack)
{
    assert(stack == NULL);
    if (stack != NULL)
    { 
        return;
    }

    Node * freeMe;

    while(!isEmpty(stack))
    {
        // go to item below top before freeing the top
        freeMe = stack->top;
        stack->top = freeMe->below;

        assert(freeMe->cargo != NULL);

        free(freeMe->cargo);
        free(freeMe);
    }

    free(stack);
}

void push(void * data, Stack * stack)
{
    assert(stack != NULL);
    if (stack == NULL)
    {
        return;
    }

    Node * newTop = (Node *) malloc(sizeof(Node));

    assert(newTop != NULL);
    if (newTop == NULL)
    {
        return;
    }

    newTop->cargo = data;

    // add to top of stack structure
    newTop->below = stack->top;
    stack->top = newTop;

}

void * pop(Stack * stack)
{
    assert(stack != NULL);
    if (stack == NULL || isEmpty(stack))
    {
        return NULL;
    }

    Node * popMe = stack->top;
    void * cargo = popMe->cargo;

    stack->top = popMe->below;

    free(popMe);

    return cargo;
}

int isEmpty(Stack * stack)
{
    assert(stack != NULL);
    if (stack != NULL)
    {
        return stack->top == NULL;
    }
    return 1; // undefined really, but better to signal that there's nothing there than allow operations on it
}