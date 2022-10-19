#include "headers/hashing.h"

int hash_mod(int cod, int n)
{
    return cod%n;
}

void THash_inicia_simples(THash_simples *hash){
  
    hash->tam = 0;

    for(int i = 0; i < TAM_TABELA; i++){
        hash->Func_info_array[i].func_cod = -1;
        hash->Func_info_array[i].RRN = 0;      
    }
}

void THash_insere_simples(THash_simples *hash, Func_info item){


    int mod = hash_mod(item.func_cod, TAM_TABELA);

    if(hash->Func_info_array[mod].func_cod == -1){
        hash->Func_info_array[mod] = item;
        hash->tam++;
    }else{
        printf("\n !! Espaco %i ocupado !! \n", mod);
    }
}

void imprime_tab_hash_simples(THash_simples *hash){
      
    for (int i = 0; i < TAM_TABELA; i++)
    {

        if(hash->Func_info_array[i].func_cod != -1){
            printf("\n_______________ Espaco %i _______________\n\n", i);

            
            printf("* Funcionario %i \n", hash->Func_info_array[i].func_cod);

            printf("\n______________________________________\n\n");
        }else{
            printf("\n_______________ Espaco %i _______________\n\n", i);

            printf("* Espaco Vazio\n");

            printf("\n______________________________________\n\n");
        }
    }
    
}

// =============================================================

void THash_inicia_encad_externo(THash_encad_externo *hash, int tam_lista)
{

    int i;
    hash->tam = 0;
    hash->tam_lista = tam_lista;

    // inicializando as listas
    hash->List_array = (TLista *)malloc(sizeof(TLista) * tam_lista);
    for (i = 0; i < tam_lista; i++)
    {
        Tlista_inicia_encad_externo(&hash->List_array[i]);
    }
}

void Tlista_inicia_encad_externo(TLista *lista)
{

    lista->pPrimeiro = NULL;
    lista->pUltimo = NULL;
    lista->qtd = 0;
}

void THash_insere_encad_externo(THash_encad_externo *hash, Func_info item)
{

    int mod = hash_mod(item.func_cod, TAM_TABELA);

    Tlista_insere_encad_externo(&hash->List_array[mod], item);

    hash->tam++;
}

int Tlista_eh_vazia_encad_externo(TLista *lista)
{
    return (lista->pPrimeiro == NULL);
}

void Tlista_insere_encad_externo(TLista *lista, Func_info item)
{

    Tcelula *new = (Tcelula *)malloc(sizeof(Tcelula));

    new->func_info = item;
    new->prox = NULL;

    if (Tlista_eh_vazia_encad_externo(lista))
    {
        lista->pPrimeiro = new;
        lista->pUltimo = new;
    }
    else
    {
        lista->pUltimo->prox = new;
        lista->pUltimo = new;
    }

    lista->qtd++;
}

void imprime_tab_hash_encad_externo(THash_encad_externo *hash)
{

    for (int i = 0; i < hash->tam_lista; i++)
    {

        Tcelula *inicio = hash->List_array[i].pPrimeiro;

        printf("\n_______________ Lista %i _______________\n\n", i);

        while (inicio != NULL)
        {
            printf("* Funcionario %i \n", inicio->func_info.func_cod);
            inicio = inicio->prox;
        }

        printf("\n______________________________________\n\n");
    }
}