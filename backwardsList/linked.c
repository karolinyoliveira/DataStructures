//Karoliny Oliveira - 10368020
#include "linked.h"
typedef struct node node_t;
struct node
{
    void *chave;
    int tempo;
    int posicao;
    node_t *prev, *next, *back;
};

struct linked
{
    node_t *head, *tail;
};

linked_t *linked_create()
{
    linked_t *l;
    l = (linked_t *)malloc(sizeof(linked_t));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

void linked_destroy(linked_t *l)
{
    if (l->head)
    {
        node_t *aux = l->head;
        do
        {
            l->head = l->head->next;
            free(aux);
            aux = l->head;
        } while (aux != l->head);

        free(l);
    }
}

int linked_insert(linked_t *l, void *x, int sizeElem, int backPositions, int time)
{
    if (!l)
        return 0;

    //Inicialização do Nó
    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->chave = malloc(sizeElem);
    memcpy(p->chave, x, sizeElem);
    p->tempo = time;
    p->posicao = 0;

    node_t *aux, *prev;
    prev = NULL;
    aux = l->head;

    while (aux)
    {
        prev = aux;
        aux = aux->next;
        p->posicao++;
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
            l->tail = p;

            p->next = NULL;
            l->tail = NULL;
        }
        p->prev = prev;
    }
    for (int i = 0; i < backPositions; i++)
    {
        p->back = p->prev;
        if (!p->prev)
        {
            p->back = l->head;
            break;
        }
        p->prev = p->prev->prev;
    }
    p->posicao -= backPositions;
    return 1;
}

int linked_remove(linked_t *l, void *x, int sizeElem)
{
    if (!l)
        return 0;
    node_t *p = l->head;
    node_t *prev = l->head->prev;
    node_t *searchBack = l->head; //para anular os possiveis p->backs direcionados ao node removido
    node_t *aux = l->head;        //para decrementar todos as p->posicoes à direita
    int posicao = 0;
    while (p && *(int *)x != *(int *)p->chave) //Busca
    {
        prev = p;
        p = p->next;
        posicao++;
    }
    p->posicao=posicao;
    if (!p)
        return 0;
    if (p == l->head) //Primeiro elemento
    {
        while (searchBack)
        {
            if (p->posicao == searchBack->posicao)
                searchBack->back = NULL;
            searchBack = searchBack->next;
        }
        aux = p;
        while (aux)
        {
            aux->posicao--;
            aux = aux->next;
        }
        l->head = p->next;
        free(p);
    }
    else
    {
        while (searchBack)
        {
            //printf("removido nó: %d p: %d // sB: %d do nó:%d\n",*(int*)p->chave,p->posicao,searchBack->posicao,*(int*)searchBack->chave);
            if (p->posicao == searchBack->posicao)
                searchBack->back = NULL;
            searchBack = searchBack->next;
        }
        aux = p;
        while (aux)
        {
            aux->posicao--;
            aux = aux->next;
        }
        prev->next = p->next;
        p->next->prev = prev;
        free(p);
    }

    return 1;
}

void linked_print(linked_t *l)
{

    if (!l->head)
    {
        printf("-1");
        return;
    }

    node_t *node = l->head;

    while (node)
    {
        printf("[%d,%d", *(int *)node->chave, node->tempo);
        if (node->back)
            if (node->posicao>0)
                printf(",%d] ", node->posicao);
            else
                printf(",%d] ", 0);
        else
            printf("] ");
        node = node->next;
    };
    printf("\n");

    return;
}