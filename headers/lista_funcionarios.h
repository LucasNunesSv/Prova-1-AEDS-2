#ifndef LISTA_CLIENTES_H
#define LISTA_CLIENTES_H


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "funcionarios.h"

typedef struct ListaFuncionarios{
    TFunc **lista;
    int qtd;
} ListaFuncionarios;

void imprime_lista_funcionarios(ListaFuncionarios *lf){
    for(int i = 0; i < lf->qtd; i++){
        toString(lf->lista[i]);
    }
}

ListaFuncionarios *cria_lista_vazia(int qtd_max_funcionarios){
    ListaFuncionarios *lf = (ListaFuncionarios *) malloc(sizeof(ListaFuncionarios));
    lf->qtd = 0;
    lf->lista = (TFunc **) malloc(sizeof(TFunc *) * (qtd_max_funcionarios));
    return lf;
}

void insere_funcionario(ListaFuncionarios *lf, TFunc *func){
    if(lf->qtd == 0){
        lf->lista[lf->qtd] = func;
    }else{
        lf->lista[lf->qtd+1] = func;
    }
}

ListaFuncionarios *cria_funcionario(int qtd, ...){
    va_list ap;
    ListaFuncionarios *lf = (ListaFuncionarios *) malloc(sizeof(ListaFuncionarios));
    lf->qtd = qtd;
    lf->lista = (TFunc **) malloc(sizeof(TFunc *) * (qtd));
    int i;
    va_start(ap, qtd);
    for(i = 0; i < qtd; i++){
        lf->lista[i] = va_arg(ap, TFunc *);
    }
    va_end(ap);
    return lf;
}

void salva_funcionarios(char *nome_arquivo, ListaFuncionarios *lf){
    FILE *out = fopen(nome_arquivo, "wb");
    for(int i = 0; i < lf->qtd; i++){
        salva_arq(lf->lista[i], out);
    }
    fclose(out);
}

ListaFuncionarios * le_funcionarios(char *nome_arquivo){
    int qtd = 0;
    ListaFuncionarios *lf = (ListaFuncionarios *) malloc(sizeof(ListaFuncionarios));
    FILE *in = fopen(nome_arquivo, "rb");
    if(in != NULL){
        TFunc *funcionario = NULL;
        while((funcionario = le(in)) != NULL){
            qtd ++;
            free(funcionario);
        }
        fseek(in, 0, SEEK_SET);
        lf->qtd = qtd;
        lf->lista = (TFunc **) malloc(sizeof(TFunc*) * (qtd));
        qtd = 0;
        while((funcionario = le(in)) != NULL){
            lf->lista[qtd++] = funcionario;
        }
        fclose(in);
    }else{
        lf->qtd = 0;
        lf->lista = NULL;
        printf("\n[ERRO AO ABRIR ARQUIVO]\n");
    }
    return lf;
}

int cmp_funcionarios(ListaFuncionarios *f1, ListaFuncionarios *f2){
	if (f1->qtd != f2->qtd) {
		return 0;
	}
	int i;
	for (i = 0; i < f1->qtd; i++) {
		if (!cmp_funcionario(f1->lista[i], f2->lista[i])) {
			return 0;
		}
	}
	return 1;
}

void libera_funcionarios(ListaFuncionarios *lf){
    for(int i = 0; i < lf->qtd; i++){
        free(lf->lista[i]);
    }
    free(lf->lista);
    free(lf);
}

#endif