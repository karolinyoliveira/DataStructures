//Karoliny Oliveira - 10368020
#include "stack.h"

struct stack
{
    int sizeStack;
    int topo;
    void **itens;
    int sizeElem;
};

stack_t *create(int sizeElem, int sizeStack)
{
    stack_t *p = (stack_t *)malloc(sizeof(stack_t));
    assert(p != NULL);
    p->sizeStack = sizeStack;
    p->itens = (void **)malloc(sizeof(void *) * p->sizeStack);
    assert(p->itens != NULL);
    p->topo = -1;
    p->sizeElem = sizeElem;
    return p;
}

void destroy(stack_t *p)
{
    while ((p->topo) > 0 && (p->topo)<(p->sizeStack-1))
    {
        free(p->itens[p->topo]);
        p->topo--;
    }

    if (p->itens != NULL)
        free(p->itens);
    if (p != NULL)
        free(p);
    p = NULL;
    return;
}

int isFull(stack_t *p)
{
    assert(p != NULL);
    if (p->topo == p->sizeStack - 1)
        return 1;
    else
        return 0;
}

int isEmpty(stack_t *p)
{
    assert(p != NULL);
    if (p->topo == -1)
        return 1;
    else
        return 0;
}

int push(stack_t *p, void *x)
{
    assert(p != NULL);
    if (isFull(p) == 1)
    {
        return -1;
    }
    p->topo++;
    p->itens[p->topo] = (void *)malloc(p->sizeElem);
    assert(p->itens[p->topo] != NULL);
    memcpy(p->itens[p->topo], x, p->sizeElem);
    return 1;
}

int pop(stack_t *p, void *x)
{
    assert(p != NULL);
    if (isEmpty(p) == 1)
    {
        return -1;
    }
    memcpy(x, p->itens[p->topo], p->sizeElem);
    free(p->itens[p->topo]);
    p->topo--;
    return 1;
}

int top(stack_t *p, void *x)
{
    assert(p != NULL);
    if (isEmpty(p) == 1)
    {
        return -1;
    }
    memcpy(x, p->itens[p->topo], p->sizeElem);
    return 1;
}