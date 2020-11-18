//Karoliny Oliveira - 10368020
#include "linked.h"
int main(void)
{
    int time = 0, n, j;
    linked_t *list=linked_create();
    char comando = 0;
    do
    {
        scanf("%c", &comando);
        switch (comando)
        {
        case 'i':
        {
            scanf("%d %d", &n, &j);
            linked_insert(list,(void*)&n,sizeof(int),j,time);
            time++;
            break;
        }
        case 'r':
        {
            scanf("%d", &n);
            linked_remove(list,(void*)&n,sizeof(int));
            time++;
            break;
        }
        default:
            break;
        }        
    } while (comando != 'f');

    linked_print(list);
    linked_destroy(list);
    return 0;
}