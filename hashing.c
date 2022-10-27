#include "headers/hashing.h"

int hash_mod(int cod, int n)
{
    return cod % n;
}

void THash_inicia_simples(THash_simples *hash)
{

    hash->tam = 0;

    for (int i = 0; i < TAM_TABELA; i++)
    {
        hash->Func_info_array[i].func_cod = -1;
        hash->Func_info_array[i].RRN = 0;
    }
}

void THash_insere_simples(THash_simples *hash, Func_info item)
{

    int mod = hash_mod(item.func_cod, TAM_TABELA);

    if (hash->Func_info_array[mod].func_cod == -1)
    {
        hash->Func_info_array[mod] = item;
        hash->tam++;
    }
    else
    {
        printf("\n !! [COLISAO] - Espaco %i ocupado !! \n", mod);
    }
}

void gerar_particoes_hash_simpl(THash_simples *hash, Nomes *nomes_arq_saida, char *nome_arq_entrada)
{

    FILE *arq;   // declara o ponteiro p/ arquivo de entrada

    // abre o arq para leitura
    if ((arq = fopen(nome_arq_entrada, "rb")) == NULL)
    {
        printf("[ERRO 3] nao foi possivel abrir o arquivo");
    }
    else
    {

        for (int i = 0; i < TAM_TABELA; i++)
        {

            FILE *p; // arq de partições

            char *nome_particao = nomes_arq_saida->nome; // pega o nome da primeira partição

            if ((p = fopen(nome_particao, "wb")) == NULL)
            {
                printf("[ERRO 2] nao foi possivel criar arquivo de saida");
            }
            else
            {
                Func_info info = hash->Func_info_array[i];
                int pos = 0;

                fseek(arq, info.RRN, SEEK_SET);
                TFunc *func = le(arq);

                fseek(p, pos * sizeof(TFunc), SEEK_SET);
                salva_arq(func, p);
                

                fclose(p); 

                nomes_arq_saida = nomes_arq_saida->prox;
            }
        }
    }
}

void imprime_tab_hash_simples(THash_simples *hash)
{

    for (int i = 0; i < TAM_TABELA; i++)
    {
        printf("cod: %i - RRN: %lf", hash->Func_info_array[i].func_cod, hash->Func_info_array->RRN);
    }

    for (int i = 0; i < TAM_TABELA; i++)
    {

        if (hash->Func_info_array[i].func_cod != -1)
        {
            printf("\n_______________ Espaco %i _______________\n\n", i);

            printf("* Funcionario %i  -  RRN: %i\n", hash->Func_info_array[i].func_cod, hash->Func_info_array[i].RRN);

            printf("\n________________________________________\n\n");
        }
        else
        {
            printf("\n_______________ Espaco %i _______________\n\n", i);

            printf("* Espaco Vazio\n");

            printf("\n________________________________________\n\n");
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

void gerar_particoes_hash_endExt(THash_encad_externo *hash, Nomes *nomes_arq_saida, char *nome_arq_entrada)
{
    
    FILE *arq;   // declara o ponteiro p/ arquivo de entrada

    // abre o arq para leitura
    if ((arq = fopen(nome_arq_entrada, "rb")) == NULL)
    {
        printf("[ERRO 3] nao foi possivel abrir o arquivo");
    }
    else
    {

        for (int i = 0; i < TAM_TABELA; i++)
        {

            FILE *p; // arq de partições

            char *nome_particao = nomes_arq_saida->nome; // pega o nome da primeira partição

            if ((p = fopen(nome_particao, "wb")) == NULL)
            {
                printf("[ERRO 2] nao foi possivel criar arquivo de saida");
            }
            else
            {
                Tcelula *inicio = hash->List_array[i].pPrimeiro;
                int pos = 0;

                while (inicio != NULL)
                {
                    fseek(arq, inicio->func_info.RRN, SEEK_SET);
                    TFunc *func = le(arq);

                    fseek(p, pos * sizeof(TFunc), SEEK_SET);
                    salva_arq(func, p);
                    inicio = inicio->prox;
                    pos++;
                }

                fclose(p); 

                nomes_arq_saida = nomes_arq_saida->prox;
            }
        }
    }
}

void imprime_tab_hash_encad_externo(THash_encad_externo *hash)
{

    for (int i = 0; i < hash->tam_lista; i++)
    {

        Tcelula *inicio = hash->List_array[i].pPrimeiro;

        printf("\n_______________ Lista %i _______________\n\n", i);

        while (inicio != NULL)
        {
            printf("* Funcionario %i  -  RRN: %i\n", inicio->func_info.func_cod, inicio->func_info.RRN);
            inicio = inicio->prox;
        }

        printf("\n________________________________________\n\n");
    }
}