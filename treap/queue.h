//Karoliny Oliveira - 10368020
#ifndef queue_H
#define queue_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue queue_t;

queue_t *queue_create(int sizeElem, int sizeStack);
void queue_destroy(queue_t *p);
int queue_insert(queue_t *p, void *x);
int queue_remove(queue_t *p, void *x);
int queue_isFull(queue_t *p);
int queue_isEmpty(queue_t *p);

#endif