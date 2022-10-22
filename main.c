#define NOME_ARQUIVO_ENTRADA "entrada.dat"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "headers\funcionarios.h"
#include "headers\nomes.h"
#include "headers\geracao_particoes.h"
#include "headers\hashing.h"

// Criado por Vanessa Braganholo em 16/09/2018
// Atualizado por: Lucas Nunes Silveira - 20.2.8040 / Matheus Lopes Moreira - 20.2.8002

// Vars globais

int base_verify = 0, arq_ordenado_verify = 0, qtd_funcionarios, hash_verify = 0;
Nomes *nomes = NULL;
Nomes *p;
THash_encad_externo tabela_hash;
THash_simples tabela_hash_simples;

void criar_bd();
void exec_Keysorting(FILE *arq, FILE *arq_ordenado);
void exec_insertion_sort(FILE *arq_ins);
void exec_busca_sequencial(FILE *arq);
void imprime_bd(FILE *arq, FILE *arq_ordenado);
void selec_sub();
void selec_nat();
void exec_hash_externo();
void imprime_hash_externo();
void exec_hash_simples();
void imprime_hash_simples();

int main(){

    // Vars

    FILE *arq = fopen(NOME_ARQUIVO_ENTRADA, "wb+");
    FILE *arq_ordenado = fopen("dados_KEY.dat", "wb+");
    FILE *arq_ins = fopen("dados_INS.dat", "wb+");
    int condicao;

    if (arq == NULL)
    {
        printf("\n!!! ERRO AO ABRIR ARQUIVO !!!");
        return 1;
    }

    if (arq_ordenado == NULL)
    {
        printf("\n!!! ERRO AO ABRIR ARQUIVO !!!");
        return 1;
    }

    do
    {
        printf("\n               ___ MENU ___\n");
        printf("\n[1] - Criar Base de Dados\n[2] - Procurar Funcionario por KEY_SORTING");
        printf("\n[3] - Procurar funcionario por INSERTION_SORT\n[4] - Procurar funcionario por BUSCA_SEQUENCIAL\n");
        printf("[5] - Imprimir base de dados completa\n[6] - Gerar particoes usando Selecao por substituicao\n");
        printf("[7] - Gerar particoes usando selecao natural\n[8] - Gerar tabela HASH Enderecamento Simples \n");
        printf("[9] - Imprimir tabela HASH: Enderecamento Simples \n[10] - Gerar tabela HASH Enderecamento Externo \n");
        printf("[11] - Imprimir tabela HASH: Enderecamento Externo \n[0] - Sair\n");

        printf("\nDigite a opcao desejada: ");
        scanf("%i", &condicao);

        switch (condicao)
        {
        case 1:
            criar_bd(arq, arq_ins);
            break;
        case 2:
            if (base_verify == 0)
            {
                printf("\n!!! E necessario criar uma base de dados antes de buscar por um funcionario !!!\n");
                break;
            }
            else
            {
                exec_Keysorting(arq, arq_ordenado);
            }
            break;
        case 3:
            if (base_verify == 0)
            {
                printf("\n!!! E necessario criar uma base de dados antes de buscar por um funcionario !!!\n");
                break;
            }
            else
            {
                exec_insertion_sort(arq_ins);
            }
            break;
        case 4:
            if (base_verify == 0)
            {
                printf("\n!!! E necessario criar uma base de dados antes de buscar por um funcionario !!!\n");
                break;
            }
            else
            {
                exec_busca_sequencial(arq);
            }
            break;
        case 5:
            if (base_verify == 0)
            {
                printf("\n!!! E necessario criar uma base de dados antes de imprimi-la !!!\n");
                break;
            }
            else
            {
                imprime_bd(arq, arq_ordenado);
            }
            break;
        case 6:
            if (base_verify == 0)
            {
                printf("\n!!! E necessario criar uma base de dados antes de gerar particoes !!!\n");
                break;
            }
            selec_sub();
            break;
        case 7:
            if (base_verify == 0)
            {
                printf("\n!!! E necessario criar uma base de dados antes de gerar particoes !!!\n");
                break;
            }
            selec_nat();
            break;
        case 8:
            if (base_verify == 0)
            {
                printf("\n!!! E necessario criar uma base de dados antes de gerar tabelas hash !!!\n");
                break;
            }
            exec_hash_simples(arq);
            break;
        case 9:
            if (base_verify == 0)
            {
                printf("\n!!! E necessario criar uma base de dados antes de imprimir tebelas hash !!!\n");
                break;
            }
            imprime_hash_simples();
            break;
        case 10:
            if (base_verify == 0)
            {
                printf("\n!!! E necessario criar uma base de dados antes de gerar tabelas hash !!!\n");
                break;
            }
            exec_hash_externo(arq);
            break;
        case 11:
            if (base_verify == 0)
            {
                printf("\n!!! E necessario criar uma base de dados antes de imprimir tebelas hash !!!\n");
                break;
            }
            imprime_hash_externo();
            break;
        case 0:
            printf("\n## Obrigado por usar este programa :) ##\n");
            break;
        default:
            printf("\n !!! Opacao invalida, tente novamente !!!\n");
            break;
        }
    } while (condicao != 0);

    fclose(arq);
    fclose(arq_ordenado);
    fclose(arq_ins);
    free(nomes);
    free(p);

    return 0;
}

void criar_bd(FILE *arq, FILE *arq_ins)
{
    printf("\nQuantos funcionarios serao inseridos na base de dados? [min: 0, max: 100] _ ");
    scanf("%i", &qtd_funcionarios);
    if (qtd_funcionarios > 100 || qtd_funcionarios <= 0)
    {
        printf("\n!! Quantidade invalida !! / min = 0 e max = 100\n");
    }
    else
    {
        cria_base_de_dados(arq, qtd_funcionarios); // Cria uma database no arquivo com funcionarios de códigos aleatórios
        cria_base_de_dados(arq_ins, qtd_funcionarios);
        printf("\n*** Base de dados criada com sucesso\n");
        base_verify++;
    }
}

void exec_Keysorting(FILE *arq, FILE *arq_ordenado)
{

    clock_t start_time_bin, end_time_bin;
    int tot_comp_bin = 0, func_cod;
    double temp_exe_bin = 0.0;
    TFunc *func;

    printf("\nDigite o codigo do funcionario que deseja buscar: _ ");
    scanf("%i", &func_cod);
    Key_sorting_file(arq, arq_ordenado, qtd_funcionarios); // Key_sorting é chamada recebendo o arquivo desordenado dados_KEY.dat, o arquivo vazio dados_ordenados.dat e a quantidade de funcionarios cadastrados. Ao fim da execução teremos o arquivo dados_ordenados.dat preenchido ordenadamente

    start_time_bin = clock(); // Início da contagem do tempo de execução da busca sequencial
    func = buscaBinaria(func_cod, qtd_funcionarios, arq_ordenado, &tot_comp_bin);
    end_time_bin = clock(); // Término da contagem do tempo de execução da busca binaria

    temp_exe_bin += (double)(end_time_bin - start_time_bin) / CLOCKS_PER_SEC; // Cálculo do tempo de execução da busca binaria

    printf("\n\n________ ## Teste utilizando a Busca Binaria (KEY_SORTING) ## ________\n\n");
    if (func == NULL)
    {
        printf("Funcionario inexistente na base de dados\n");
        printf("______________________________________________________________________\n\n");
    }
    else
    {
        printf("Funcionario encontrado: Imprimindo...");
        toString(func);
    }
    printf("\n## No de comparacoes da busca Binaria: %i", tot_comp_bin);
    printf("\n## Tempo gasto na Execucao da busca Binaria: %.6f s\n", temp_exe_bin);
    printf("______________________________________________________________________\n\n");

    arq_ordenado_verify++;
}

void exec_insertion_sort(FILE *arq_ins)
{

    clock_t start_time_bin, end_time_bin;
    int tot_comp_bin = 0, func_cod;
    double temp_exe_bin = 0.0;
    TFunc *func;

    printf("\nDigite o codigo do funcionario que deseja buscar: _ ");
    scanf("%i", &func_cod);

    insertion_sort_disco(arq_ins, qtd_funcionarios);

    start_time_bin = clock(); // Início da contagem do tempo de execução da busca binaria
    func = buscaBinaria(func_cod, qtd_funcionarios, arq_ins, &tot_comp_bin);
    end_time_bin = clock(); // Término da contagem do tempo de execução da busca binaria

    temp_exe_bin += (double)(end_time_bin - start_time_bin) / CLOCKS_PER_SEC; // Cálculo do tempo de execução da busca binaria

    printf("\n\n________ ## Teste utilizando a Busca Binaria (INSERTION_SORTING) ## ________\n\n");
    if (func == NULL)
    {
        printf("Funcionario inexistente na base de dados\n");
        printf("____________________________________________________________________________\n\n");
    }
    else
    {
        printf("Funcionario encontrado: Imprimindo...");
        toString(func);
    }
    printf("\n## No de comparacoes da busca Binaria: %i", tot_comp_bin);
    printf("\n## Tempo gasto na Execucao da busca Binaria: %.6f s\n", temp_exe_bin);
    printf("____________________________________________________________________________\n\n");
}

void exec_busca_sequencial(FILE *arq)
{

    clock_t start_time_seq, end_time_seq;
    int tot_comp_seq = 0, func_cod;
    double temp_exe_seq = 0.0;
    TFunc *func;

    printf("\nDigite o codigo do funcionario que deseja buscar: _ ");
    scanf("%i", &func_cod);
    start_time_seq = clock(); // Início da contagem do tempo de execução da busca sequencial
    func = busca_sequencial(func_cod, arq, qtd_funcionarios, &tot_comp_seq);
    end_time_seq = clock(); // Término da contagem do tempo de execução da busca sequencial

    temp_exe_seq += (double)(end_time_seq - start_time_seq) / CLOCKS_PER_SEC; // Cálculo do tempo de execução da busca sequencial

    printf("\n\n________ ## Teste utilizando a Busca Sequencial ## ________\n\n");
    if (func == NULL)
    {
        printf("!!! Funcionario inexistente na base de dados\n");
        printf("\n                 ##### Observacao #####\n\nO Codigo dos funcionarios eh gerado de forma aleatoria\ntente executar novamente ou usar outro codigo\n");
        printf("____________________________________________________________\n\n");
    }
    else
    {
        printf("Funcionario encontrado: Imprimindo...");
        toString(func);
    }
    printf("\n## No de comparacoes da busca sequencial: %i", tot_comp_seq);
    printf("\n## Tempo gasto na Execucao da busca sequencial: %.6f s\n", temp_exe_seq);
    printf("____________________________________________________________\n\n");
}

void imprime_bd(FILE *arq, FILE *arq_ordenado)
{

    int cond_bd;
    TFunc *func;

    printf("\nPara imprimir a base de dados ORDENADA tecle [1]\nPara imprimir a base de dados DESORDENADA tecle [2]\nopcao: _ ");
    scanf("%i", &cond_bd);
    if (cond_bd == 1)
    {
        if (arq_ordenado_verify != 0)
        {
            for (int i = 0; i < qtd_funcionarios; i++)
            {
                fseek(arq_ordenado, i * sizeof(TFunc), SEEK_SET);
                func = le(arq_ordenado);
                toString(func);
            }
        }
        else
        {
            printf("\n!!! E necessario realizar o Key sorting antes de imprimir os dados ordenados !!!\n");
        }
    }
    else if (cond_bd == 2)
    {
        for (int i = 0; i < qtd_funcionarios; i++)
        {
            fseek(arq, i * sizeof(TFunc), SEEK_SET);
            func = le(arq);
            toString(func);
        }
    }
    else
    {
        printf("\n!!! Opcao invalida, tente novamente !!!\n");
    }
}

void selec_sub()
{

    printf("\n Gerando particoes com SELECAO_SUBSTITUICAO...\n");

    nomes = cria_nomes(cria_str("p_ss1.dat"),
                       cria_nomes(cria_str("p_ss2.dat"),
                                  cria_nomes(cria_str("p_ss3.dat"),
                                             cria_nomes(cria_str("p_ss4.dat"),
                                                        cria_nomes(cria_str("p_ss5.dat"),
                                                                   cria_nomes(cria_str("p_ss6.dat"),
                                                                              cria_nomes(cria_str("p_ss7.dat"),
                                                                                         cria_nomes(cria_str("p_ss8.dat"),
                                                                                                    cria_nomes(cria_str("p_ss9.dat"), NULL)))))))));

    selecao_com_substituicao(NOME_ARQUIVO_ENTRADA, nomes, 6);

    printf("\nParticoes geradas com sucesso !!\n");
}

void selec_nat()
{

    printf("\nGerando particoes com SELECAO_NATURAL...\n");

    nomes = cria_nomes(cria_str("p_sn1.dat"),
                       cria_nomes(cria_str("p_sn2.dat"),
                                  cria_nomes(cria_str("p_sn3.dat"),
                                             cria_nomes(cria_str("p_sn4.dat"),
                                                        cria_nomes(cria_str("p_sn5.dat"),
                                                                   cria_nomes(cria_str("p_sn6.dat"),
                                                                              cria_nomes(cria_str("p_sn7.dat"),
                                                                                         cria_nomes(cria_str("p_sn8.dat"),
                                                                                                    cria_nomes(cria_str("p_sn9.dat"), NULL)))))))));

    selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

    printf("\nParticoes geradas com sucesso !!\n");
}

void exec_hash_externo(FILE *arq)
{

    Func_info info_array[qtd_funcionarios];

    THash_inicia_encad_externo(&tabela_hash, TAM_TABELA);

    rewind(arq);

    for (int i = 0; i < qtd_funcionarios; i++)
    {
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        info_array[i].RRN = ftell(arq);
        TFunc *func = le(arq);
        info_array[i].func_cod = func->cod;

        THash_insere_encad_externo(&tabela_hash, info_array[i]);
    }

    printf("\n!! Tabela hash criada com sucesso !! \n");

    hash_verify++;
}

void imprime_hash_externo()
{

    if (hash_verify == 0)
    {
        printf("\n!!! E necessario gerar uma tabela hash antes de imprimi-la !!!\n");
    }
    else
    {
        imprime_tab_hash_encad_externo(&tabela_hash);
    }
}

void exec_hash_simples(FILE *arq){

    Func_info info_array_simples[qtd_funcionarios];

    THash_inicia_simples(&tabela_hash_simples);

    rewind(arq);

    for (int i = 0; i < qtd_funcionarios; i++)
    {
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        info_array_simples[i].RRN = ftell(arq);
        TFunc *func = le(arq);
        info_array_simples[i].func_cod = func->cod;

        THash_insere_simples(&tabela_hash_simples, info_array_simples[i]);
    }

    printf("\n!! Tabela hash criada com sucesso !! \n");

    hash_verify++;    
}

void imprime_hash_simples()
{
    if (hash_verify == 0)
    {
        printf("\n!!! E necessario gerar uma tabela hash antes de imprimi-la !!!\n");
    }
    else
    {
        imprime_tab_hash_simples(&tabela_hash_simples);
    }
}