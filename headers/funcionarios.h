#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

// Lucas Nunes Silveira - 20.2.8040
// Matheus Lopes Moreira - 20.2.8002

#define MAXTAM 2
#define MAXTAM_ARVB 511

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Funcionario
{
   int cod;
   char nome[50];
   char cpf[15];
   char data_nascimento[11];
   float salario;
   //  int qtd_comparacoes;
} TFunc;

typedef struct key_sorting
{
   int cod; // key
   long RRN;
} Key_sorting;

void toString(TFunc *func);

void salva_arq(TFunc *func, FILE *arq);

TFunc *le(FILE *in);

void cria_base_de_dados(FILE *arq, int nFunc);

TFunc *busca_sequencial(int cod, FILE *arq, int tam_arq, int *comp);

TFunc *buscaBinaria(int cod, int qtd_func, FILE *arq, int *comp);

void insertion_sort_disco(FILE *arq, int qtd_func);

void Key_sorting_file(FILE *arq, FILE *arq_ordenado, int qtd_func);

void ordena_array(Key_sorting *array, int qtd_func);

TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nasc, float salario);

int cmp_funcionario(TFunc *f1, TFunc *f2);

void selec_sub();

void selec_nat();

#endif
