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
// void le_funcionario(TFunc *func);
void salva_no_arq(TFunc *func, FILE *arq);
TFunc *le(FILE *in);
void cria_base_de_dados(FILE *arq, int qtdFunc);
TFunc *busca_binaria(int cod, FILE *arq, int tam);