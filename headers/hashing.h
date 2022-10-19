#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcionarios.h"

#define TAM_TABELA 7

typedef struct Func_info{
    int func_cod; // key
    long RRN;
}Func_info;

typedef struct Tcelula{
    Func_info func_info;
    struct Tcelula *prox;
} Tcelula;

typedef struct{
    Tcelula *pPrimeiro, *pUltimo;
    int qtd;
} TLista;

typedef struct {
    TLista *List_array; // array de listas
    int tam_lista; // tamanho do array de listas 
    int tam; // numero de funcionarios na tabela hash
} THash;

int hash_mod(int cod, int n);

void THash_inicia(THash *hash, int tam_lista);

void Tlista_inicia(TLista *lista);

void Cria_infoArray(Func_info array[], char *nome_arq, int qtd_func);

void THash_insere(THash *hash, Func_info item);

int Tlista_eh_vazia(TLista *lista);

void Tlista_insere(TLista *lista, Func_info item);

void imprime_tab_hash(THash *hash);