#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct funcionariosTeste{
    int cod;
    char nome[50];
    char cpf[15];
    char data_de_nascimento[11];
    double salario;
}Tfunc;

void salva_arq(Tfunc *func, FILE *out);
Tfunc *le(FILE *in);
void cria_base_de_dados(FILE *arq, int qtd_func);
Tfunc *busca_binaria(int cod, FILE *arq, int tam_arq);
Tfunc *busca_sequencial(int cod, FILE *arq, int tam_arq);


#endif