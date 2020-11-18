//Karoliny Oliveira - 10368020
#ifndef linked_H
#define linked_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked linked_t;

linked_t *linked_create();
void linked_destroy(linked_t *l);
int linked_insert(linked_t *l, void *x, int sizeElem);
void linked_print(linked_t *l);
void sum (linked_t *x,linked_t *y);
int big (linked_t *x,linked_t *y);
void sml (linked_t *x,linked_t *y);
void eql (linked_t *x,linked_t *y);

#endif