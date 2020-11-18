//Karoliny Oliveira - 10368020
#ifndef linked_H
#define linked_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked linked_t;

linked_t *linked_create();
void linked_destroy(linked_t *p);
void* linked_iterate(linked_t *p, int n, int k);
int linked_insert(linked_t *l, void *x, int sizeElem, int nInsertions, int * counter);
int linked_remove(linked_t *l, void *x, int sizeElem);
void imprimir(linked_t *l);
#endif