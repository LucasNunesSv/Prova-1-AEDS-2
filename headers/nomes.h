#ifndef NOMES_H
#define NOMES_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Nomes
{
    char *nome;
    struct Nomes *prox;
} Nomes;

char *cria_str(char *str);

Nomes *cria_nomes(char *nome, Nomes *prox);

void libera_nomes(Nomes *nomes);

int conta_nomes(Nomes *nomes);

void inverte_nomes(Nomes *nomes);

void imprime_nomes(Nomes *nomes);

#endif