#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Lucas Nunes Silveira - 20.2.8040
// Matheus Lopes Moreira - 20.2.8002

#define MAXTAM 2

 typedef struct Funcionario {
     int cod;
     char nome[50];
     char cpf[15];
     char data_nascimento[11];
     float salario;
    //  int qtd_comparacoes;
 }TFunc;

 typedef struct key_sorting{
    int cod; //key
    long RRN;
 }Key_sorting;

void toString(TFunc *func);
void salva_arq(TFunc *func, FILE *arq);
TFunc *le(FILE *in);
void cria_base_de_dados(FILE *arq, int qtdFunc);
TFunc *busca_sequencial(int cod, FILE *arq, int tam_arq, int *comp);
TFunc *buscaBinaria (int cod, int qtd_func, FILE *arq, int *comp);
void insertion_sort_disco(FILE *arq, int qtd_func);
void Key_sorting_file(FILE *arq, FILE *arq_ordenado, int qtd_func);
void ordena_array(Key_sorting *array, int qtd_func);
