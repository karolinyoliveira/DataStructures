//Karoliny Oliveira - 10368020
#ifndef skip_H
#define skip_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

typedef struct skip skip_t;
#define MAXLEVEL 20
#define MAXWORD 51
#define MAXDEF 141

/*
* Inicializa a skip list, com o primeiro nó de cabeçalho.
*
*@param NULL
*@return Ponteiro para a skip list vazia
*/
skip_t *skip_create();

/*
* Faz a impressão da palavra e definição correspondente, caso exista.
*
*@param dict skiplist dicionário
*@param str1 palavra
*@return void
*/
void skip_search(skip_t *dict, char *str1);

/*
* Insere um novo elemento no dicionário.
*
*@param dict skiplist dicionário
*@param str1 palavra
*@param str2 definição
*@return void
*/
void skip_insert(skip_t *dict, char *str1, char *str2);

/*
* Modifica a definição da palavra desejada.
*
*@param dict skiplist dicionário
*@param str1 palavra
*@param str2 definição
*@return void
*/
void skip_change(skip_t *dict, char *str1, char *str2);

/*
* Remove/Desaloca o nó vinculado à palavra indicada na Skip List.
*
*@param dict skiplist dicionário
*@param str1 palavra
*@return void
*/
void skip_remove(skip_t *dict, char *str1);

/*
* Imprime todas as palavras e definições iniciadas pela letra indicada.
*
*@param dict skiplist dicionário
*@param ch1 letra
*@return void
*/
void skip_print(skip_t *dict, char ch1);

/*
* Desaloca todos as strings, nós e skip lists alocados.
*
*@param dict skiplist dicionário
*@return void
*/
void skip_destroy(skip_t *dict);

#endif