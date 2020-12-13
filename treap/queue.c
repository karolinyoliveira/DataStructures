//Karoliny Oliveira - 10368020
#include "queue.h"

struct queue
{
    int inicio, fim, total;
    void **itens;
    int sizeQueue;
    int sizeElem;
};

queue_t *queue_create(int sizeElem, int sizeQueue)
{
    queue_t *p;
    p = (queue_t *)malloc(sizeof(queue_t));
    if (p == NULL)
        return (queue_t *)EXIT_FAILURE;

    p->itens = (void **)malloc(sizeof(void *) * p->sizeQueue);
    if (p->itens == NULL)
        return (queue_t *)EXIT_FAILURE;
    p->sizeElem = sizeElem;
    p->sizeQueue = sizeQueue;
    p->total = 0;
    p->inicio = 0;
    p->fim = 0;
    return p;
}

int queue_isFull(queue_t *p)
{
    if (p == NULL)
        return 0;
    if (p->total == p->sizeQueue)
        return 1;
    return 0;
}

int queue_isEmpty(queue_t *p)
{
    if (p == NULL)
        return 0;
    if (p->total == 0)
        return 1;
    return 0;
}

int queue_insert(queue_t *p, void *x)
{
    if (queue_isFull(p) == 1)
        return 0;
    p->itens[p->fim] = (void *)malloc(p->sizeElem);
    if (p->itens[p->fim] == NULL)
        return 0;
    memcpy(p->itens[p->fim], x, p->sizeElem);
    p->fim = (p->fim + 1) % p->sizeQueue;
    p->total++;
    return 1;
}

int queue_remove(queue_t *p, void *x)
{
    if (queue_isEmpty(p) == 1)
        return 0;
    memcpy(x, p->itens[p->inicio], p->sizeElem);

    p->inicio = (p->inicio + 1) % p->sizeQueue;
    p->total--;
    return 1;
}

void queue_destroy(queue_t *p)
{
    if (p != NULL)
        free(p);
}