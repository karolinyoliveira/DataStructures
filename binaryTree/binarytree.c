//Karoliny Oliveira - 10368020
#include "binarytree.h"
struct node
{
    int data;
    node_t *left, *right;
};

binTree_t *binTree_create()
{
    binTree_t *t = (binTree_t *)malloc(sizeof(binTree_t));
    t->root = NULL;
    return t;
}

int binTree_insertLeft(binTree_t *t, int x, int dad)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->left = NULL;
    p->right = NULL;
    p->data = x;
    if (dad == -1)
    {
        if (!t->root)
        {
            t->root = p;
        }
        else
        {
            free(p);
            return 0;
        }
    }
    else
    {
        node_t *tmp = binTree_search(t->root, dad);
        if (tmp && !tmp->left)
            tmp->left = p;
        else
        {
            free(p);
            return 0;
        }
    }
    return 1;
}
int binTree_insertRight(binTree_t *t, int x, int dad)
{
    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->left = NULL;
    p->right = NULL;
    p->data = x;
    if (dad == -1)
    {
        if (!t->root)
        {
            t->root = p;
        }
        else
        {
            free(p);
            return 0;
        }
    }
    else
    {
        node_t *tmp = binTree_search(t->root, dad);
        if (tmp && !tmp->right)
            tmp->right = p;
        else
        {
            free(p);
            return 0;
        }
    }
    return 1;
}
node_t *binTree_parentSearch(node_t *root, int x)
{
    if (!root)
        return NULL;
    if (root->left && root->left->data == x)
        return root;
    if (root->right && root->right->data == x)
        return root;

    node_t *p = binTree_parentSearch(root->left, x);
    if (!p)
        p = binTree_parentSearch(root->right, x);
    return p;
}

node_t *binTree_search(node_t *root, int x)
{
    if (!root)
        return NULL;
    if (root->data == x)
        return root;
    node_t *p = binTree_search(root->left, x);
    if (!p)
        p = binTree_search(root->right, x);
    return p;
}

int binTree_isEmpty(binTree_t *t)
{
    if (!t)
        return 0;
    if (!t->root)
        return 1;
    return 0;
}

void binTree_finish(node_t *root)
{
    if (root)
    {
        binTree_finish(root->left);
        binTree_finish(root->right);
        free(root);
    }
}

void binTree_print(node_t *root)
{
    if (root)
    {
        printf("%d(", root->data);
        binTree_print(root->left);
        printf(",");
        binTree_print(root->right);
        printf(")");
    }
    else
        printf("null");
}

int binTree_height(node_t *root)
{
    if (!root)
        return 0;
    int height_l = 1 + binTree_height(root->left);
    int height_r = 1 + binTree_height(root->right);
    if (height_l > height_r)
        return height_l;
    return height_r;
}

int binTree_remove(binTree_t *t, int x)
{
    return 0;
}

void preOrder(node_t *node, node_t*root)
{
    if (node)
    {
        binTree_analyze(node,root);
        preOrder(node->left,root);
        preOrder(node->right,root);
    }
}

void inOrder(node_t *root)
{
    if (root)
    {
        inOrder(root->left);
        printf("%d\n", root->data);
        inOrder(root->right);
    }
}

void postOrder(node_t *root)
{
    if (root)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d\n", root->data);
    }
}

//no %d: pai = %d, altura = %d, grau = %d, filhos = (%d,%d), tipo = type
void binTree_analyze(node_t *node,node_t* root)
{
    if (!node)
        return;
    printf("no %d: ", node->data);

    //Pai
    node_t *dad = binTree_parentSearch(root, node->data);

    if (dad)
        printf("pai = %d, ", dad->data);
    else
        printf("pai = -1, ");

    printf("altura = %d, ", binTree_height(node));

    //Grau
    int counter = 0;
    if (node->left)
        counter++;
    if (node->right)
        counter++;
    printf("grau = %d, ", counter);

    //Filhos
    switch (counter)
    {
    case 0:
    {
        printf("filhos = (-1,-1), ");
        break;
    }
    case 1:
    {
        if (node->left)
        {
            printf("filhos = (%d,-1), ", node->left->data);
            break;
        }
        printf("filhos = (-1,%d), ", node->right->data);
        break;
    }
    case 2:
    {
        printf("filhos = (%d,%d), ", node->left->data, node->right->data);
        break;
    }
    default:
        break;
    }

    //Tipo
    if (!dad)
    {
        printf("tipo = raiz\n");
        return;
    }
    if (!counter)
    {
        printf("tipo = folha\n");
        return;
    }
    printf("tipo = interno\n");
    return;
}
