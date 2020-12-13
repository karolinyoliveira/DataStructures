//Karoliny Oliveira - 10368020

/*
* Implementação de uma árvore binária de busca + Heap (Treap) com as seguintes funções(O):
*
* 1. Inserção
* 2. Busca
* 3. Remoção
* 4. Impressão
*/

#include "treap.h"
int main(void)
{
    int n, x, prioridade;
    scanf("%d", &n);
    char comando[10], modo[10];
    treap_t *tree = treap_create();
    for (int i = 0; i < n; i++)
    {
        scanf("%s ", comando);
        switch (comando[1])
        {
        case 'n': //Inserção
            scanf("%d", &x);
            scanf("%d", &prioridade);
            tree->root = treap_insert(tree->root, x, prioridade);
            break;
        case 'u': //Busca
            scanf("%d", &x);
            if (treap_search(tree->root, x))
                printf("1\n");
            else
                printf("0\n");
            break;
        case 'e': //Remoção
            scanf("%d", &x);
            scanf("%d", &prioridade);
            tree->root = treap_remove(tree->root, x, prioridade);
            break;
        case 'm': //Impressão
            scanf(" %s", modo);
            treap_print(tree->root, modo);
            break;
        default:
            break;
        }
    }
    treap_finish(tree->root);
    return 0;
}
