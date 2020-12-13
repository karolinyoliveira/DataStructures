//Karoliny Oliveira - 10368020
#ifndef treap_H
#define treap_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node node_t;

typedef struct treap
{
    node_t *root;
} treap_t;

/*
* Aloca espaço para uma nova árvore vazia.
*
* @return ponteiro para a árvore criada
*/
treap_t *treap_create();

/*
* Desaloca todos os nós e árvore desejada.
*
* @param root raíz da árvore
*
* @return void
*/
void treap_finish(node_t *root);

/*
* Insere um novo nó pelas regras da BST para x e da estrutura de dados MAX Heap para prioridade
*
* @param root raíz da árvore
* @param x valor inserido
* @param prioridade utilizado na ordenação heap
*
* @return nó com a nova raíz, após inserção
*/
node_t *treap_insert(node_t *root, int x, int prioridade);

/*
* Busca por um nó de determinado valor na árvore. Similar a busca em BST.
*
* @param root raíz da árvore desejada
* @param x valor buscado
*
* @return o nó encontrado e NULL caso não encontre 
*/
node_t *treap_search(node_t *root, int x);

/*
* Faz a impressão conforme o modo desejado: em ordem, pré ordem, pós ordem ou em largura.
*
* @param x
* @param mode
*
* @return void
*/
void treap_print(node_t *root, char *mode);

/*
* Faz a remoção de x da Treap
*
* @param x 
*
* @return raíz após remoção
*/
node_t *treap_remove(node_t *root, int x, int prioridade);

#endif
