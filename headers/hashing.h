#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcionarios.h"

#define TAM_TABELA 7

typedef struct Func_info
{
    int func_cod; // key
    long RRN;
} Func_info;

typedef struct Tcelula
{
    Func_info func_info;
    struct Tcelula *prox;
} Tcelula;

typedef struct
{
    Tcelula *pPrimeiro, *pUltimo;
    int qtd;
} TLista;

typedef struct
{
    Func_info Func_info_array[TAM_TABELA]; // array de posicoes
    int tam;            // numero de funcionarios na tabela hash
} THash_simples;

typedef struct
{
    TLista *List_array; // array de listas
    int tam_lista;      // tamanho do array de listas
    int tam;            // numero de funcionarios na tabela hash
} THash_encad_externo;

int hash_mod(int cod, int n);

void THash_inicia_simples(THash_simples *hash);

void THash_insere_simples(THash_simples *hash, Func_info item);

void imprime_tab_hash_simples(THash_simples *hash);

// =============================================================

void THash_inicia_encad_externo(THash_encad_externo *hash, int tam_lista);

void Tlista_inicia_encad_externo(TLista *lista);

void THash_insere_encad_externo(THash_encad_externo *hash, Func_info item);

int Tlista_eh_vazia_encad_externo(TLista *lista);

void Tlista_insere_encad_externo(TLista *lista, Func_info item);

void imprime_tab_hash_encad_externo(THash_encad_externo *hash);