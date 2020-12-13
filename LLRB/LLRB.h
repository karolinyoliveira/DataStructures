//Karoliny Oliveira - 10368020
#ifndef LLRB_H
#define LLRB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node node_t;

typedef struct rbTree
{
    node_t *root;
} rbTree_t;

/*
* Aloca espaço para uma nova árvore vazia.
*
* @return ponteiro para a árvore criada
*/
rbTree_t *rbTree_create();

/*
* Desaloca todos os nós e árvore desejada.
*
* @param root raíz da árvore
*
* @return void
*/
void rbTree_finish(node_t *root);

/*
* Insere um novo nó pelas regras da árvore binária de busca rubro-negra (Left-Leaning).
*
* @param root raíz da árvore
* @param x valor inserido
*
* @return nó com a nova raíz, após inserção
*/
node_t *rbTree_insert(node_t *root, int x);

/*
* Busca por um nó de determinado valor na árvore. Similar a busca em BST.
*
* @param root raíz da árvore desejada
* @param x valor buscado
*
* @return o nó encontrado e NULL caso não encontre 
*/
node_t *rbTree_search(node_t *root, int x);

/*
* Encontra o sucessor de x nos nós da árvore ordenada.
*
* @param root raíz da árvore analisada
* @param x valor desejado
*
* @return sucessor de x
*/
int rbTree_nextNode(node_t *root, int x);

/*
* Encontra o predecessor de x nos nós da árvore ordenada.
*
* @param root raíz da árvore analisada.
* @param x valor desejado.
*
* @return predecessor de x
*/
int rbTree_prevNode(node_t *root, int x);

/*
* Encontra o menor valor da árvore cuja raíz foi fornecida.
*
* @param root 
*
* @return valor mínimo da árvore
*/
int rbTree_min(node_t *root);

/*
* Encontra o maior valor da árvore cuja raíz foi fornecida.
*
* @param root 
*
* @return valor máximo da árvore
*/
int rbTree_max(node_t *root);

//Percursos
void preOrder(node_t *root);
void inOrder(node_t *root);
void postOrder(node_t *root);

#endif
