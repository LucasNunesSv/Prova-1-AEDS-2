#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionarios.h"

int main(){

    // Variáveis
    FILE *arq = fopen("dados.dat", "wb+");
    clock_t start_time_seq, end_time_seq, start_time_bin, end_time_bin;
    double temp_exe_seq = 0.0, temp_exe_bin = 0.0;
    int qtd_de_Func = 1000;
    int buscar_Func_cod = 999;
    int key_array[qtd_de_Func];
     
    if(arq == NULL){
        printf("\n!!! ERRO AO ABRIR ARQUIVO !!!");
        return 1;
    }
    
    cria_base_de_dados(arq, qtd_de_Func);
    
    start_time_seq = clock();
    TFunc *func = busca_sequencial(buscar_Func_cod, arq, qtd_de_Func);
    end_time_seq = clock();
    
    temp_exe_seq += (double)(end_time_seq-start_time_seq)/CLOCKS_PER_SEC;
    
    printf("________ ## Teste utilizando a Busca Sequencial ## ________\n\n");
    if(func == NULL){
        printf("Funcionario inexistente na base de dados");
        return 1;
    }else{
        printf("Funcionario encontrado: Imprimindo...");
        toString(func);
    }

    printf("\n## No de comparacoes da busca sequencial: %i", func->qtd_comparacoes);
    printf("\n## Tempo gasto na Execucao da busca sequencial: %lf s\n", temp_exe_seq);
    printf("____________________________________________________________\n\n");

    key_sorting(arq, &key_array, qtd_de_Func);
    insertion_sort(&key_array, qtd_de_Func); // Implementação da função de ordenação InsertioSort, embora o vetor ja esteja ordenado

    start_time_bin = clock();
    int cod = buscaBinaria(buscar_Func_cod, qtd_de_Func, &key_array);
    for(int i=0; i<500000; i++){
        
    }
 
    end_time_bin = clock();

    temp_exe_bin += (double)(end_time_bin-start_time_bin)/CLOCKS_PER_SEC;
    
    printf("\n## Tempo gasto na Execucao da busca Binaria: %lf s\n", temp_exe_bin);


    printf("\n\n________ ## Teste utilizando a Busca Binaria ## ________\n\n");
    int verification = 0;
    for(int i=0; i<qtd_de_Func; i++){
        if(key_array[i] == cod){
            verification ++;
        }
    }
    if(verification == 0){
        printf("Funcionario inexistente na base de dados");
    }else{
        printf("Funcionario encontrado: Imprimindo...");
        fseek(arq, cod*sizeof(TFunc), SEEK_SET);
        func = le(arq);
        toString(func);
    }
    printf("____________________________________________________________\n\n");

    free(func);
    fclose(arq);

    return 0;
}

void toString(TFunc *func){

    printf("\n\nNome: %s", func->nome);
    printf("\nCPF: %s", func->cpf);
    printf("\nCodigo: %i", func->cod);
    printf("\nData de nascimento: %s", func->data_nascimento);
    printf("\nSalario: %.2f", func->salario);
    printf("\n");

}

void salva_no_arq(TFunc *func, FILE *arq){
    
    fwrite(&func->cod, sizeof(int), 1, arq);
    fwrite(func->nome, sizeof(char), sizeof(func->nome), arq);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), arq);
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

int buscaBinaria (int cod, int qtd_func, int *array) { 

   int e = -1, d = qtd_func; 
   int qtd_comp = 0;

   if(cod > qtd_func){
    return NULL;
   }

    while (e < d-1) {    
        int m = (e + d)/2;
        if (array[m] < cod){
            e = m; qtd_comp++; 
        }
        else {
            d = m; qtd_comp++;
        }
    }
    if(qtd_comp>qtd_func)
    printf("O codigo não esta contido no array");
    else
    printf("\n## No de comparacoes da busca Binaria: %i", qtd_comp);
  
   return d;
}

TFunc *busca_sequencial(int cod, FILE *arq, int tam_arq){

    int qtd_comp = 0;

    for(int i=0; i<tam_arq; i++){
        qtd_comp ++;
        fseek(arq, i*sizeof(TFunc), SEEK_SET);
        TFunc *func = le(arq);
        if(func->cod == cod){
            func->qtd_comparacoes = qtd_comp;
            return func;
        }
    }

    return NULL;

}

void key_sorting(FILE *arq, int *key_array, int qtd_func){

    for(int i=0; i<qtd_func; i++){
        fseek(arq, i*sizeof(TFunc), SEEK_SET);
        TFunc *func = le(arq);
        key_array[i] = func->cod;
    }

}

void insertion_sort(int *array, int qtd_func){

    int i, j, tmp;
  
    for(i = 1; i < qtd_func; i++){
    tmp = array[i];
    for(j = i-1; j >= 0 && tmp < array[j]; j--){
        array[j+1] = array[j];
    }
    array[j+1] = tmp;
    }

}


/* _____ ## Anotações ## ______

# 1ª tentativa da função de busca binaria

int busca_binaria(int *array, int qtd_func, int cod){
    
    int begin = 0;
    int end = qtd_func - 1;
    

    while (begin <= end) {  // Condição de parada 
        int i = (begin + end) / 2;  // Calcula o meio do sub-vetor 
        if (array[i] == cod) {  // Item encontrado 
            return i;
        }
        if (array[i] < cod) {  // Item está no sub-vetor à direita 
            begin = i + 1;
        } else {  // vector[i] > item. Item está no sub-vetor à esquerda 
            end = i;
        }
    }
    return -1;
}

*/