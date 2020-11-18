//Karoliny Oliveira - 10368020
#include "linked.h"
typedef struct node node_t;
struct node
{
    void *data;
    node_t *prev, *next;
};

struct linked
{
    node_t *head, *tail;
};

linked_t *linked_create()
{
    linked_t *p;
    p = (linked_t *)malloc(sizeof(linked_t));
    p->head = NULL;
    p->tail = NULL;
    return p;
}

void linked_destroy(linked_t *p)
{
    if (p)
    {
        node_t *aux = p->head;
        do
        {
            p->head = p->head->next;
            free(aux);
            aux = p->head;
        } while (aux != p->head);

        free(p);
    }
}

int linked_insert(linked_t *l, void *x, int sizeElem, int nInsertions, int *counter)
{
    if (!l)
        return 0;
    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->data = malloc(sizeElem);
    memcpy(p->data, x, sizeElem);

    node_t *aux, *prev;
    prev = NULL;
    aux = l->head;

    while (aux && x > aux->data) // Mantém a ordenação crescente
    {
        prev = aux;
        aux = aux->next;
    }

    if (aux && x == aux->next) //Não permite valor já existente
    {
        free(p);
        return 0;
    }

    if (!prev) //Início
    {
        p->prev = l->head;
        if (l->head)
            l->head->prev = p;
        l->head = p;
        l->head->next = NULL;
    }
    else //Fim ou Meio
    {
        p->next = prev->next;

        prev->next = p;
        if (p->next)
        {
            p->next = p;
        }
        else
        {
            *counter++;
            l->tail = p;
            if (nInsertions == *counter) //Fecha o ciclo após todas as inserções
            {
                p->next = l->head;
                l->tail = l->head;
                l->head->prev = p;
            }
        }
        p->prev = prev;
    }
    *counter++;
    return 1;
}

int linked_remove(linked_t *l, void *x, int sizeElem)
{
    if (!l)
        return 0;
    node_t *p = l->head;

    node_t *prev = l->head->prev;

    while (p && x > p->data) //Busca
    {
        prev = p;
        p = p->next;
    }

    if (!p)
        return 0;

    if (p == l->head) //Primeiro elemento
    {

        l->head = l->head->next;
        if (l->head)
        {
            l->head->prev = l->head->prev->prev;
            l->head->prev->next = l->head;
        }
        
        free(p);
    }
    else
    {
        prev->next = p->next;
        p->next->prev = prev;
        free(p);
    }
    return 1;
}

/*
* Avança k posições na lista encadeada circular n-1 vezes, removendo os nós selecionados. Quando sobrar um, o valor é printado 
*/
void *linked_iterate(linked_t *p, int n, int k)
{
    if (!p)
        return NULL;
    node_t *node = p->head;
    node_t *prev = p->head->prev;

    void *val = node->data;

    int i = 0;
    for (i = 1; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            prev = node;
            node = node->next;
            val = node->data;
        }
        linked_remove(p, prev->data, sizeof(int));
    }
    printf("%d\n", *(int *)val);
    return val;
}

void imprimir(linked_t *l)
{
    if (!l)
        return;
    node_t *node = l->head;
    do
    {
        printf("%d ", *(int *)node->data);
        node = node->next;
    } while (node != l->head);

    printf("\n");
}