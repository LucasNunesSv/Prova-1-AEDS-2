#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXTAM 2

 typedef struct Funcionario {
     int cod;
     char nome[50];
     char cpf[15];
     char data_nascimento[11];
     float salario;
     int qtd_comparacoes;
 }TFunc;

void toString(TFunc *func);
void salva_arq(TFunc *func, FILE *arq);
TFunc *le(FILE *in);
void cria_base_de_dados(FILE *arq, int qtdFunc);
TFunc *busca_sequencial(int cod, FILE *arq, int tam_arq);
int buscaBinaria (int cod, int qtd_func, int *array);
void key_sorting(FILE *arq, int *key_array, int qtd_func);
void insertion_sort(int *array, int qtd_func);
void insertion_sort_disco(FILE *arq, int qtd_func);
