//Karoliny Oliveira - 10368020
#ifndef binarytree_H
#define binarytree_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node node_t;

typedef struct binarytree
{
    node_t *root;
} binTree_t;

binTree_t *binTree_create();
int binTree_insertLeft(binTree_t *t, int x, int dad);
int binTree_insertRight(binTree_t *t, int x, int dad);
node_t *binTree_parentSearch(node_t *root, int x);
node_t *binTree_search(node_t *root, int x);
int binTree_isEmpty(binTree_t *t);
void binTree_finish(node_t *root);
void binTree_print(node_t *root);
int binTree_height(node_t *root);
int binTree_remove(binTree_t *t, int x);

//Traversals
void preOrder(node_t *node, node_t*root); //Modified
void inOrder(node_t *root);
void postOrder(node_t *root);

//main.c exercise
void binTree_analyze(node_t *node,node_t* root);

#endif
