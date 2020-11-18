//Karoliny Oliveira - 10368020
#include "linked.h"
int main(void)
{
    int T, n, k, counter=0, casos=1;
    scanf("%d", &T);
    linked_t *cycle;
    while (T)
    {
        cycle = linked_create();
        scanf("%d", &n);
        scanf("%d", &k);
        for (int i = 1; i <= n; i++)
        {
            linked_insert(cycle, (void *)&i, sizeof(int), n, &counter);
        }
        printf("Caso %d: ", casos); 
        linked_iterate(cycle, n, k);
        linked_destroy(cycle);
        counter=0;
        T--;
        casos++;
    }
    return 0;
}