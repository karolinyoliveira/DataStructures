//Karoliny Oliveira - 10368020
#include "linked.h"
int main(void)
{
    int n, counter = 1;
    linked_t *x;
    linked_t *y;

    char comando[4], digit;
    scanf("%d", &n);
    while ((n - counter) >= 0)
    {
        scanf("%s ", comando);

        //Read Values
        x = linked_create();
        y = linked_create();

        digit = getc(stdin);
        while (digit != ' ')
        {
            linked_insert(x, (void *)&digit, sizeof(char));
            digit = getc(stdin);
        };

        digit = getc(stdin);
        while (digit != '\n' && digit!='\r' && digit!=EOF)
        {
            linked_insert(y, (void *)&digit, sizeof(char));
            digit = getchar();
        };

        //Calculate
        printf("Resultado %d: ", counter);
        switch (comando[1])
        {
        case 'u': //sum
        {
            sum(x, y);
            break;
        }
        case 'i': //bigger than
        {
            big(x, y);
            break;
        }
        case 'm': //smaller than
        {
            sml(x, y);
            break;
        }
        case 'q': //equal to
        {
            eql(x, y);
            break;
        }
        default:
            break;
        };
        linked_destroy(x);
        linked_destroy(y);
        counter++;
    };

    return 0;
}