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
    int size;
    int signal; // 0 for positive and 1 for negative
};

linked_t *linked_create()
{
    linked_t *l;
    l = (linked_t *)malloc(sizeof(linked_t));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    l->signal = 0;
    return l;
}

void linked_destroy(linked_t *l)
{
    if (l)
    {
        node_t *aux = l->head;
        do
        {
            l->head = l->head->next;
            free(aux);
            aux = l->head;
        } while (aux != NULL);
        free(l);
    }
    return;
}

int linked_insert(linked_t *l, void *x, int sizeElem)
{
    if (!l)
        return 0;
    if (*(char *)x == '-')
    {
        l->signal = 1;
        return 0;
    }

    node_t *p = (node_t *)malloc(sizeof(node_t));
    p->data = malloc(sizeElem);
    memcpy(p->data, x, sizeElem);

    node_t *aux, *prev;
    prev = NULL;
    aux = l->head;
    while (aux)
    {
        prev = aux;
        aux = aux->next;
    }

    if (!l->head) //Início
    {
        l->head = p;
        l->tail = p;
        p->next = NULL;
        p->prev = NULL;
    }
    else //Fim
    {
        l->tail->next = p;
        l->tail = p;
        p->next = NULL;
        p->prev = prev;
    }
    l->size++;
    return 1;
}

void linked_print(linked_t *l)
{
    if (!l)
        return;
    int skipZeros = 0;
    node_t *node = l->tail;
    do
    {
        if (*(char *)node->data != '0')
            skipZeros++;
        if (skipZeros)
            printf("%c", *(char *)node->data);
        node = node->prev;
    } while (node != NULL);
        printf("\n");

}

void sum(linked_t *x, linked_t *y)
{
    int carry = 0;
    linked_t *result = linked_create();

    // Sum until node_x and node_y existis
    node_t *node_x = x->tail;
    node_t *node_y = y->tail;
    do
    {
        int digit = (*(char *)node_x->data - '0') + (*(char *)node_y->data - '0') + carry;
        carry = 0;

        if (digit > 9)
        {
            digit = digit % 10;
            carry = 1;
        }
        char char_digit = digit + '0';
        linked_insert(result, (void *)&char_digit, sizeof(char));
        node_x = node_x->prev;
        node_y = node_y->prev;
    } while (node_x != NULL && node_y != NULL);

    // If x has MORE digits than y
    while (node_x)
    {
        int digit = (*(char *)node_x->data - '0') + carry;
        carry = 0;

        if (digit > 9)
        {
            digit = digit % 10;
            carry = 1;
        }
        char char_digit = digit + '0';
        linked_insert(result, (void *)&char_digit, sizeof(char));
        node_x = node_x->prev;
    }

    // If x has LESS digits than y
    while (node_y)
    {
        int digit = (*(char *)node_y->data - '0') + carry;
        carry = 0;

        if (digit > 9)
        {
            digit = digit % 10;
            carry = 1;
        }
        char char_digit = digit + '0';
        linked_insert(result, (void *)&char_digit, sizeof(char));
        node_y = node_y->prev;
    }
    if (carry)
    {
        char carry1 = '1';
        linked_insert(result, (void *)&carry1, sizeof(char));
    }
    linked_print(result);
    linked_destroy(result);
    return;
}

int big(linked_t *x, linked_t *y)
{
    //Signal
    if (x->signal < y->signal)
    {
        printf("1\n");
        return 1;
    }
    if (x->signal > y->signal)
    {
        printf("0\n");
        return 0;
    }

    //Size
    if (x->size > y->size)
    {
        printf("1\n");
        return 1;
    }
    if (x->size < y->size)
    {
        printf("0\n");
        return 0;
    }

    //Same size and signal evaluate
    node_t *node_x = x->head;
    node_t *node_y = y->head;

    do
    {
        if (*(char *)node_x->data < *(char *)node_y->data)
        {
            if (x->signal)
            {
                printf("1\n");
                return 1;
            }
            printf("0\n");
            return 0;
        }
        if (*(char *)node_x->data > *(char *)node_y->data)
        {
            if (x->signal)
            {
                printf("0\n");
                return 0;
            }
            printf("1\n");
            return 1;
        }
        node_x = node_x->next;
        node_y = node_y->next;
    } while (node_x != NULL && node_y != NULL);
    printf("0\n");
    return 0;
}

void sml(linked_t *x, linked_t *y)
{
    //Signal
    if (x->signal < y->signal)
    {
        printf("0\n");
        return;
    }
    if (x->signal > y->signal)
    {
        printf("1\n");
        return;
    }

    //Size
    if (x->size > y->size)
    {
        printf("0\n");
        return;
    }
    if (x->size < y->size)
    {
        printf("1\n");
        return;
    }

    //Same size and signal evaluate
    node_t *node_x = x->head;
    node_t *node_y = y->head;

    do
    {
        if (*(char *)node_x->data < *(char *)node_y->data)
        {
            printf("1\n");
            return;
        }
        if (*(char *)node_x->data > *(char *)node_y->data)
        {
            printf("0\n");
            return;
        }
        node_x = node_x->next;
        node_y = node_y->next;
    } while (node_x != NULL && node_y != NULL);
    printf("0\n");
    return;
}

void eql(linked_t *x, linked_t *y)
{
    //Signal
    if (x->signal != y->signal)
    {
        printf("0\n");
        return;
    }

    //Size
    if (x->size != y->size)
    {
        printf("0\n");
        return;
    }

    //Same size evaluate
    node_t *node_x = x->tail;
    node_t *node_y = y->tail;

    do
    {
        if (*(char *)node_x->data != *(char *)node_y->data)
        {
            printf("0\n");
            return;
        }
        node_x = node_x->prev;
        node_y = node_y->prev;
    } while (node_x != NULL && node_y != NULL);
    printf("1\n");
    return;
}