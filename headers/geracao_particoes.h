#ifndef GERACAO_PARTICOES_H
#define GERACAO_PARTICOES_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "nomes.h"
#include "funcionarios.h"
#include "stdbool.h"
#include "string.h"

typedef struct FuncAux
{
    TFunc *Funcionario;
    // 0 para True e 1 para false
    int congelado;
} FuncAux;

void selecao_com_substituicao(char *nome_arq_entrada, Nomes *nome_aqrs_saida, int M);

void selecao_natural(char *nome_arq_entrada, Nomes *nome_arqs_saida, int M, int n);

void initFronzenArray(char *array, int M);

int fullXFrozenArray(char *array, int m);

int getMinIndexWithFrozen(int M, TFunc **memory, char *frozen);

int estaVazio(TFunc **vetor, int n);

int reservatorioTransferToMemory(FILE *reservatorio, TFunc **memory, int indexReservatorio, int M);

int getMinIndex(int M, TFunc **memory);

#endif
