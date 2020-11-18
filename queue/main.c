//Karoliny Oliveira - 10368020
#include "queue.h"
typedef struct person
{
    char nome[50];
    int idade;
    int saude;
} pessoa;
int main(void)
{
    int N, flag;
    scanf("%d", &N);
    queue_t *filas[4];
    for (int i = 0; i < 4; i++)
    {
        filas[i] = queue_create(sizeof(pessoa), N); //N considerando o espaço máximo que a fila pode ter
    }

    char opcao[6];
    pessoa nova_pessoa;
    int prioridade = 3;
    for (int i = 0; i < N; i++)
    {
        scanf("%s", opcao);
        switch (opcao[0])
        {
        case 'E':
            scanf("%s", nova_pessoa.nome);
            scanf("%d", &nova_pessoa.idade);
            scanf("%d", &nova_pessoa.saude);
            if (queue_isFull(filas[3]))
            {
                printf("FILA CHEIA\n");
                break;
            }

            //Prioridade
            if (nova_pessoa.idade >= 60)
            {
                prioridade = 2;
                if (nova_pessoa.saude == 1)
                    prioridade = 0;
            }
            else
            {
                if (nova_pessoa.saude)
                    prioridade = 1;
                else
                    prioridade=3;
            }

            queue_insert(filas[prioridade], (void *)&nova_pessoa);

            break;
        case 'S':
            if (!queue_isEmpty(filas[0]))
            {
                queue_remove(filas[0], (void *)&nova_pessoa);
                printf("%s %d %d\n", nova_pessoa.nome, nova_pessoa.idade, nova_pessoa.saude);
                break;
            }
            if (!queue_isEmpty(filas[1]))
            {
                queue_remove(filas[1], (void *)&nova_pessoa);
                printf("%s %d %d\n", nova_pessoa.nome, nova_pessoa.idade, nova_pessoa.saude);
                break;
            }
            if (!queue_isEmpty(filas[2]))
            {
                queue_remove(filas[2], (void *)&nova_pessoa);
                printf("%s %d %d\n", nova_pessoa.nome, nova_pessoa.idade, nova_pessoa.saude);
                break;
            }
            if (!queue_isEmpty(filas[3]))
            {
                queue_remove(filas[3], (void *)&nova_pessoa);
                printf("%s %d %d\n", nova_pessoa.nome, nova_pessoa.idade, nova_pessoa.saude);
                break;
            }
            printf("FILA VAZIA\n");
            break;
        default:
            break;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        queue_destroy(filas[i]);
    }
}