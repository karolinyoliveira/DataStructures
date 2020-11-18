//Karoliny Oliveira - 10368020

//O objetivo deste projeto e desenvolver os mecanismos de manipulacao de um dicionario com definicoes de palavras ou  expressoes idiomaticas (verbetes) apresentadas pelos usuarios.
//A entrada do programa se da pela definicao da operacao a ser realizada seguida por uma ou duas cadeias de caracteres, dependendo da operacao requerida. As operacoes devem considerar a seguinte configuracao de entrada:
//  • insercao str1 str2:  insere a palavra str1, com a definicao str2, no dicionario;
//  • alteracao str1 str2:  altera a definicao da palavra str1 para str2;
//  • remocao str1:  remove a palavra str1 do dicionario;
//  • busca str1:  imprime a definicao da palavra str1;
//  • impressao ch1: imprime todas as palavras iniciadas pelo caractere ch1 seguidas por suas respectivas definicoes em ordem alfabetica.

#include "skip.h"

int main(void)
{
    srand(time(NULL)); //Usada para geração de níveis aleatórios

    skip_t *dict = skip_create();
    char comando[10];
    char str1[MAXWORD], str2[MAXDEF];
    while (scanf("%s ", comando) != EOF)
    {
        switch (comando[1])
        {
        case 'n': //insercao
        {
            scanf("%s ", str1);
            scanf("%[^\n]s", str2);
            skip_insert(dict, str1, str2);
            break;
        }
        case 'l': //alteracao
        {
            scanf("%s ", str1);
            scanf("%[^\n]s", str2);
            skip_change(dict, str1, str2);
            break;
        }
        case 'e': //remocao
        {
            scanf("%s", str1);
            skip_remove(dict, str1);
            break;
        }
        case 'u': //busca
        {
            scanf("%s", str1);
            skip_search(dict, str1);
            break;
        }
        case 'm': //impressao
        {
            char ch1;
            scanf("%c", &ch1);
            skip_print(dict, ch1);
            break;
        }
        default:
            printf("OPERACAO INVALIDA\n");
            break;
        };
    };
    skip_destroy(dict);
    return 0;
}
