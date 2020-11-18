//Karoliny Oliveira - 10368020
#ifndef stack_H
#define stack_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
typedef struct stack stack_t;

stack_t *create(int sizeElem, int sizeStack);
int push(stack_t *p, void *x);
int pop(stack_t *p, void *x);
int top(stack_t *p, void *x);
void destroy(stack_t *p);
int isFull(stack_t *p);
int isEmpty(stack_t *p);
#endif