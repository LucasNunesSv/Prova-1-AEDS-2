#include "headers/hashing.h"

int hash_mod(int cod, int n){
    return cod%n;
}

void THash_inicia(THash *hash, int tam_lista){

    int i;
    hash->tam = 0;
    hash->tam_lista = tam_lista;

    // inicializando as listas
    hash->List_array = (TLista*) malloc(sizeof(TLista) * tam_lista);
    for(i = 0; i < tam_lista; i++){
        Tlista_inicia(&hash->List_array[i]);
    }

}

void Tlista_inicia(TLista *lista){

    lista->pPrimeiro = NULL;
    lista->pUltimo = NULL;
    lista->qtd = 0;

}

void Cria_infoArray(Func_info array[], char *nome_arq, int qtd_func){

    FILE *arq;

    if((arq = fopen(nome_arq, "rb")) == NULL){
        printf("[ERRO 1] nao foi possivel abrir o arquivo");
    }else{

        for(int i=0; i<qtd_func; i++){
            fseek(arq, i*sizeof(TFunc), SEEK_SET);
            array[i].RRN = ftell(arq);
            TFunc *func = le(arq); 
            array[i].func_cod = func->cod;
        }

    }
    fclose(arq);
}

void THash_insere(THash *hash, Func_info item){

    int mod = hash_mod(item.func_cod, TAM_TABELA);

    Tlista_insere(&hash->List_array[mod], item);

    hash->tam++;

}

int Tlista_eh_vazia(TLista *lista){
    return (lista->pPrimeiro == NULL);
}

void Tlista_insere(TLista *lista, Func_info item){

    Tcelula *new = (Tcelula*)malloc(sizeof(Tcelula));

    new->func_info = item;
    new->prox = NULL;

    if(Tlista_eh_vazia(lista)){
        lista->pPrimeiro = new;
        lista->pUltimo = new;
    }else{
        lista->pUltimo->prox = new;
        lista->pUltimo = new;
    }

    lista->qtd++;

}

void imprime_tab_hash(THash *hash){
    
    for(int i = 0; i < hash->tam_lista; i++){

        Tcelula *inicio = hash->List_array[i].pPrimeiro;

        printf("\n_______________ Lista %i _______________\n\n", i);

        while(inicio != NULL){
            printf("* Funcionario %i \n", inicio->func_info.func_cod);
            inicio = inicio->prox;
        }

        printf("\n______________________________________\n\n");

    }
    
}