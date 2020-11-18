//Karoliny Oliveira - 10368020

#include "stack.h"
int main(void)
{
    printf("ok\n");
    int N, carta, rounds = 1, actualPosition = 1;
    scanf("%d", &N);
    stack_t *compra = create(sizeof(int), N);
    stack_t *descarte = create(sizeof(int), N);
    stack_t *morto = create(sizeof(int), N);
    stack_t *aux = create(sizeof(int), N);

    //Leitura
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &carta);
        push(aux, (void *)&carta);
    }
    for (int i = 0; i < N && !isEmpty(aux); i++)
    {
        pop(aux, (void *)&carta);
        push(compra, (void *)&carta);
    }

    while (!isFull(morto))
    { 
        for (int i = 0; i < N; i++)
        {
            pop(compra, (void *)&carta);
            if (actualPosition == carta)
            {
                push(morto, (void *)&carta);
                actualPosition++;
                break;
            }
            push(descarte, (void *)&carta);
        }
        if (isEmpty(compra) && !isFull(morto))
        {
            for (int i = 0; i < N && !isEmpty(descarte); i++)
            {
                pop(descarte, (void *)&carta);
                push(compra, (void *)&carta);
            }
            rounds++;
        }
    }
    printf("%d\n", rounds);

    //free!!
    destroy(compra);
    destroy(descarte);
    destroy(morto);
    destroy(aux);

    return 0;
}