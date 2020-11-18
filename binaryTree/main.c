//Karoliny Oliveira - 10368020
#include "binarytree.h"

int main(void)
{
    int n, id, esq, dir;

    scanf("%d", &n);
    int *pais = (int *)malloc(sizeof(int) * n); //pai[i] pai do nó de valor i
    int *side = (int *)malloc(sizeof(int) * n); //0 esq 1 dir
    binTree_t *t = binTree_create();
    for (int i = 0; i < n; i++)
    {
        pais[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &id);
        scanf("%d", &esq);
        scanf("%d", &dir);

        pais[esq] = id;
        side[esq] = 0;

        pais[dir] = id;
        side[dir] = 1;
    }

    //Inserção 
    for (int i = 0; i < n; i++)
    {
        if (!side[i])
            binTree_insertLeft(t, i, pais[i]);
        else
            binTree_insertRight(t, i, pais[i]);
    }

    preOrder(t->root,t->root); 
    binTree_finish(t->root);
    return 0;
}
