//Karoliny Oliveira - 10368020
#include "skip.h"
typedef struct node node_t;

//Assinatura de funções internas

/*
* Faz a busca pelo nó com a string correspondente.
*
*@param Lista de nós e a string desejada.
*@return O nó caso exista, NULL caso contrário.
*/
node_t *word_search(skip_t *dict, char *str1);

/*
* Faz a alocação de um novo nó e insere os valores indicados.
*
*@param Todos os elementos do nó.
*@return O nó criado.
*/
node_t *create_node(char *word, char *def, int level, node_t *next, node_t *down);

/*
* Retorna um nível aleatório entre 0 e o maior level da lista
*
*@param NULL
*@return int
*/
int generate_level();

//Structs
struct node
{
    char *word;
    char *def;
    int level;
    node_t *next;
    node_t *down;
};

struct skip
{
    int level;
    node_t *upleft;
};

//Funções
skip_t *skip_create()
{
    skip_t *dict;
    dict = (skip_t *)malloc(sizeof(skip_t));
    dict->level = 0;
    node_t *header = create_node("", "", 0, NULL, NULL);
    dict->upleft = header;
    return dict;
}

node_t *create_node(char *word, char *def, int level, node_t *next, node_t *down)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->word = (char *)malloc(strlen(word) + 1);
    strcpy(node->word, word);
    node->def = (char *)malloc(strlen(def) + 1);
    strcpy(node->def, def);
    node->level = level;
    node->next = next;
    node->down = down;
    return node;
}

int generate_level()
{
    int level = 0;
    while ((level < MAXLEVEL) && (rand() % 2))
        level++;
    return level;
}

void skip_destroy(skip_t *dict)
{
    if (!dict)
        return;

    node_t *aux = dict->upleft, *prev;
    dict->upleft = dict->upleft->down;
    while (dict->upleft)
    {
        while (aux)
        {
            prev = aux;
            aux = aux->next;
            free(prev->word);
            free(prev->def);
            free(prev);
        }
        aux = dict->upleft;
        dict->upleft = dict->upleft->down;
    }
    free(dict);
    return;
}

void skip_insert(skip_t *dict, char *str1, char *str2)
{
    if (!dict)
        return;

    //Desconsidera elementos já existentes
    if (word_search(dict, str1))
    {
        printf("OPERACAO INVALIDA\n");
        return;
    }

    node_t *x = dict->upleft; //sentinela
    node_t **updates = (node_t **)malloc(sizeof(node_t *) * MAXLEVEL);
    for (int i = 0; i <= dict->level; i++)
    {
        updates[i] = NULL;
    }

    //Busca da posição adequada
    int i = x->level;
    while (x && i >= 0)
    {
        while (x->next && strcmp(x->next->word, str1) < 0)
        {
            x = x->next;
        }
        updates[i] = x;
        if (x && x->down)
            x = x->down;
        i--;
    }

    //Inserção no nível mais baixo
    node_t *newNode = create_node(str1, str2, 0, x->next, NULL);
    x->next = newNode;

    //Promoção
    i = 1; //level atual
    int randomLevel = generate_level();
    while (i <= dict->level && i <= randomLevel)
    {
        if (updates[i])
        {
            node_t *promotedNode = create_node(str1, str2, i, updates[i]->next, updates[i - 1]->next);
            updates[i]->next = promotedNode;
        }
        else
            break;
        i++;
    }

    //Inserção em novo level
    if (randomLevel > dict->level)
    {
        for (int i = dict->level + 1; i <= randomLevel; i++)
        {
            if (updates[i - 1])
            {
                node_t *promotedNode = create_node(str1, str2, i, NULL, updates[i - 1]->next);

                node_t *newLevelNode = create_node("", "", i, promotedNode, dict->upleft);
                dict->upleft = newLevelNode;
                updates[i] = newLevelNode;
            }
            else
                break;
        }
        dict->level = randomLevel;
    }
    free(updates);
}

void skip_change(skip_t *dict, char *str1, char *str2)
{
    node_t *result = word_search(dict, str1);
    if (result)
    {
        result->def = (char *)realloc(result->def, strlen(str2) + 1);
        strcpy(result->def, str2);
    }
    else
        printf("OPERACAO INVALIDA\n");
}

void skip_remove(skip_t *dict, char *str1)
{
    if (!dict)
        return;

    //Verifica se a palavra existe
    if (!word_search(dict, str1))
    {
        printf("OPERACAO INVALIDA\n");
        return;
    }

    node_t *x = dict->upleft; //Sentinela
    node_t **updates = (node_t **)malloc(sizeof(node_t *) * MAXLEVEL);
    for (int i = 0; i <= dict->level; i++)
    {
        updates[i] = NULL;
    }

    //Busca top down
    while (x->level)
    {
        while (x->next && strcmp(x->next->word, str1) < 0)
        {
            x = x->next;
        }
        updates[x->level] = x;
        x = x->down;
    }

    //Busca no level 0
    while (x->next && strcmp(x->next->word, str1) < 0)
    {
        x = x->next;
    }
    updates[x->level] = x;

    //Evita remoção de cabeçalho/Lista vazia
    if ((x && !strcmp(x->word, "") && !x->next))
        return;

    //Remoção Top Down
    int i = 0;
    while (i <= dict->level)
    {
        if (updates[i]->next && !strcmp(updates[i]->next->word, str1))
        {
            node_t *rem = updates[i]->next;
            updates[i]->next = rem->next;
            free(rem->word);
            free(rem->def);
            free(rem);
        }
        i++;
    }

    //Remoção de Level
    while (!dict->upleft->next && dict->upleft->down)
    {
        node_t *rem = dict->upleft;
        free(rem->word);
        free(rem->def);
        free(rem);
        dict->upleft = dict->upleft->down;
        dict->level--;
    }
    free(updates);
}

node_t *word_search(skip_t *dict, char *str1)
{
    if (!dict)
        return NULL;
    node_t *x = dict->upleft;
    int level = x->level;

    //Busca
    while (x && level)
    {

        while (x->next && strcmp(x->next->word, str1) <= 0)
        {
            x = x->next;
        }
        if (x)
            x = x->down;
        level--;
    }

    //Busca level 0
    while (x->next && strcmp(x->next->word, str1) <= 0)
    {
        x = x->next;
    }

    if (strcmp(x->word, str1) != 0)
        return NULL;
    return x;
}

void skip_search(skip_t *dict, char *str1)
{
    node_t *result = word_search(dict, str1);
    if (result)
        printf("%s %s\n", result->word, result->def);
    else
        printf("OPERACAO INVALIDA\n");
}

void skip_print(skip_t *dict, char ch1)
{
    if (!dict)
        return;
    node_t *x = dict->upleft;
    int flag = 0;

    //Busca
    while (x && x->level > 0)
    {
        while (x->next && x->next->word[0] < ch1)
        {
            x = x->next;
        }
        x = x->down;
    }

    //Busca Level 0
    while (x->next && x->next->word[0] < ch1)
    {
        x = x->next;
    }

    while (x->next && x->next->word[0] == ch1)
    {
        printf("%s %s\n", x->next->word, x->next->def);
        x = x->next;
        flag = 1;
    }
    if (!flag)
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", ch1);
}