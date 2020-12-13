//Karoliny Oliveira - 10368020

/*
* Implementação de uma árvore binária de busca rubro-negra (Left-Leaning) com as seguintes funções(O):
*
* 1. Inserção
* 2. Sucessor de uma chave
* 3. Predecessor de uma chave
* 4. Máximo
* 5. Mínimo
* 6. Impressão preOrder 
* 7. Impressão inOrder 
* 8. Impressão postOrder
*/

#include "LLRB.h"

int main(void)
{
    int N, O, X, result;
    scanf("%d", &N);
    rbTree_t *tree = rbTree_create();
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &O);
        switch (O)
        {
        case 1:
            scanf("%d", &X);
            tree->root = rbTree_insert(tree->root, X);
            break;
        case 2:
            scanf("%d", &X);
            result = rbTree_nextNode(tree->root, X);
            if (result != -1)
                printf("%d\n", result);
            else
                printf("erro\n");
            break;
        case 3:
            scanf("%d", &X);
            result = rbTree_prevNode(tree->root, X);
            if (result != -1)
                printf("%d\n", result);
            else
                printf("erro\n");
            break;
        case 4:
            result = rbTree_max(tree->root);
            printf("%d\n", result);
            break;
        case 5:
            result = rbTree_min(tree->root);
            printf("%d\n", result);
            break;
        case 6:
            preOrder(tree->root);
            printf("\n");
            break;
        case 7:
            inOrder(tree->root);
            printf("\n");
            break;
        case 8:
            postOrder(tree->root);
            printf("\n");
            break;
        default:
            break;
        }
    }

    rbTree_finish(tree->root);
    return 0;
}
