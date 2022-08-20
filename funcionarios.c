#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionarios.h"

void toString(TFunc *func){

    printf("\n\nNome: %s", func->nome);
    printf("\nCPF: %s", func->cpf);
    printf("\nCodigo: %i", func->cod);
    printf("\nData de nascimento: %s", func->data_nascimento);
    printf("\nSalario: %.2f", func->salario);
    printf("\nNo de comparações: %i", func->qtd_comparacoes);

}

void salva_no_arq(TFunc *func, FILE *arq){

    fwrite(func->nome, sizeof(char), sizeof(func->nome), arq);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), arq);
    fwrite(&func->cod, sizeof(int), 1, arq);
    fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), arq);
    fwrite(&func->salario, sizeof(float), 1, arq);

}

TFunc *le(FILE *in){

    TFunc *func = (TFunc*) malloc(sizeof(TFunc));

    if(0 >= fread(&func->cod, sizeof(int), 1, in)){
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(float), 1, in);

    return func;
}

void cria_base_de_dados(FILE *arq, int nFunc){

    for(int i=1; i<= nFunc; i++){
        TFunc func;
        func.cod = i;
        sprintf(func.nome, "Funcionario %i", i);
        sprintf(func.cpf, "000.000.000-00");
        sprintf(func.data_nascimento, "01/01/2000");
        func.salario = 1000 + i;
        fseek(arq, (i-1)*sizeof(TFunc), SEEK_SET);
        salva_no_arq(&func, arq);
       
    }
}

TFunc *busca_binaria(int cod, FILE *arq, int tam){
    int left = 0, right = tam-1, qtd_comp = 0;
    while(left <= right){
        qtd_comp++;
        int middle = (left + right)/2;
        fseek(arq, middle*sizeof(TFunc), SEEK_SET);
        TFunc *func = le(arq);

        if(cod == func->cod){
            func->qtd_comparacoes = qtd_comp;
            return func;
        }else if(func->cod < cod){
            left = middle+1;
        }else{
            right = middle-1;
        }
    }
    return NULL;
}

int main(){

    FILE *arq = fopen("dados.dat", "wb+");
    if(arq == NULL){
        printf("\n!!! ERRO AO ABRIR ARQUIVO !!!");
        return 1;
    }
    
    int nFunc = 5;
    cria_base_de_dados(arq, nFunc);
    TFunc *func = busca_binaria(2, arq, nFunc);

    if(func == NULL){
        printf("Funcionario inexistente na base de dados");
    }else{
        printf("Funcionario encontrado: Imprimindo...\n");
        toString(func);
    }

    for(int i=0; i<nFunc; i++){
        TFunc *funcT = le(arq);
        fseek(arq, (i)*sizeof(TFunc), SEEK_SET);
        toString(funcT);

    }



    free(func);
    fclose(arq);

    return 0;
}

// void le_funcionario(TFunc *func){

//     printf("\nDigite o nome do Funcionario: ");
//     fflush(stdin);
//     gets(func->nome);
//     fflush(stdin);
//     printf("Digite o CPF do Funcionario: ");
//     gets(func->cpf);
//     fflush(stdin);
//     printf("Digite o Codigo do Funcionario: ");
//     scanf("%i", &func->cod);
//     fflush(stdin);
//     printf("Digite a data de nascimento: ");
//     gets(func->data_nascimento);
//     fflush(stdin);
//     printf("Digite o salario: ");
//     scanf("%f", &func->salario);

// }



/* ____ # CHATZINHO TRANSGENERE # _______
















*/