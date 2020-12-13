//Karoliny Oliveira - 10368020
#include "LLRB.h"

struct node
{
    int data;
    int color; //0->Black 1->Red
    node_t *left, *right;
};

//Assinatura de Funções Internas

/*
* Cria um novo nó, com a cor vermelha.
*
* @param x valor do nó
*
* @return ponteiro para o nó criado
*/
node_t *createNode(int x);

/*
* Rotaciona a subárvore no sentido antihorário
*
* @param root raíz da subárvore
*
* @return subárvore rotacionada
*/
node_t *rotateLeft(node_t *root);

/*
* Rotaciona a subárvore no sentido horário
*
* @param root raíz da subárvore
*
* @return subárvore rotacionada
*/
node_t *rotateRight(node_t *root);

/*
* Encontra o sucessor de um nó com valor x
*
* @param root ponteiro para a raíz da árvore
* @param next ponteiro em que será armazedo o sucessor
* @param x valor desejado
*
* @return void
*/
void nextNode(node_t *root, node_t **next, int x);

/*
* Encontra o predecessor de um nó com valor x
*
* @param root ponteiro para a raíz da árvore
* @param prev ponteiro em que será armazedo o predecessor
* @param x valor desejado
*
* @return void
*/
void prevNode(node_t *root, node_t **prev, int x);

//Implementações

node_t *createNode(int x)
{
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = x;
    newNode->color = 1;
    return newNode;
}

node_t *rotateLeft(node_t *root)
{
    node_t *child = root->right;
    root->right = child->left;
    child->left = root;
    if (child->left)
    {
        child->color = child->left->color;
        child->left->color = 1;
    }
    return child;
}

node_t *rotateRight(node_t *root)
{
    node_t *child = root->left;
    root->left = child->right;
    child->right = root;
    if (child->right)
    {
        child->color = child->right->color;
        child->right->color = 1;
    }
    return child;
}

rbTree_t *rbTree_create()
{
    rbTree_t *tree = (rbTree_t *)malloc(sizeof(rbTree_t));
    tree->root = NULL;
    return tree;
}

node_t *rbTree_insert(node_t *root, int x)
{
    if (!root)
        return createNode(x);

    // LLRB: Caso em que ambas as arestas filhas são vermelhas
    if (root->left && root->left->color && root->right && root->right->color)
    {
        root->color = !root->color;
        root->left->color = !root->left->color;
        root->right->color = !root->right->color;
    }

    //Inserção em uma BST normal
    if (x < root->data)
        root->left = rbTree_insert(root->left, x);

    else if (x > root->data)
        root->right = rbTree_insert(root->right, x);

    // LLRB: Caso em que filho da direita é vermelho
    if (root->right && root->right->color)
    {
        root = rotateLeft(root);
    }

    // LLRB: Caso em que filho e neto são vermelhos
    if (root->left && root->left->color && root->left->left && root->left->left->color)
    {
        root = rotateRight(root);
    }
    return root;
}

void nextNode(node_t *root, node_t **next, int x)
{
    if (!root)
        return;

    if (root->data == x)
    {
        if (root->right)
            (*next) = createNode(rbTree_min(root->right));
    }
    else if (x < root->data)
    {
        (*next) = root;
        nextNode(root->left, next, x);
    }
    else
        nextNode(root->right, next, x);
}

int rbTree_nextNode(node_t *root, int x)
{
    node_t *next = NULL;
    nextNode(root, &next, x);
    if (next)
        return next->data;
    else
        return -1;
}

void prevNode(node_t *root, node_t **prev, int x)
{
    if (!root)
        return;

    if (root->data == x)
    {
        if (root->left)
            (*prev) = createNode(rbTree_max(root->left));
    }
    else if (x < root->data)
        prevNode(root->left, prev, x);
    else
    {
        (*prev) = root;
        prevNode(root->right, prev, x);
    }
}

int rbTree_prevNode(node_t *root, int x)
{
    node_t *prev = NULL;
    prevNode(root, &prev, x);
    if (prev)
        return prev->data;
    else
        return -1;
}

int rbTree_min(node_t *root)
{
    if (!root->left)
        return root->data;
    else
        return rbTree_min(root->left);
}

int rbTree_max(node_t *root)
{
    if (!root->right)
        return root->data;
    else
        return rbTree_max(root->right);
}

node_t *rbTree_search(node_t *root, int x)
{
    if (!root)
        return NULL;
    if (root->data == x)
        return root;
    if (x < root->data)
        return rbTree_search(root->left, x);
    else
        return rbTree_search(root->right, x);
}

void rbTree_finish(node_t *root)
{
    if (root)
    {
        rbTree_finish(root->left);
        rbTree_finish(root->right);
        free(root);
    }
}

void preOrder(node_t *root)
{
    if (root)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(node_t *root)
{
    if (root)
    {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(node_t *root)
{
    if (root)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}
