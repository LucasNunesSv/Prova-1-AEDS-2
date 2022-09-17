#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionarios.h"

// Lucas Nunes Silveira - 20.2.8040
// Matheus Lopes Moreira - 20.2.8002

int main(){

    // Variáveis

    FILE *arq = fopen("dados_KEY.dat", "wb+");
    FILE *arq_ordenado = fopen("dados_ordenado.dat", "wb+");
    FILE *arq_ins = fopen("dados_INS.dat", "wb+");

    clock_t start_time_seq, end_time_seq, start_time_bin, end_time_bin;
    double temp_exe_seq = 0.0, temp_exe_bin = 0.0;
    int tot_comp_seq = 0, tot_comp_bin = 0;
    int condicao, qtd_de_Func, find_func, baseid = 0, arq_ord_id = 0;
    TFunc *func;
    
    if(arq == NULL){
        printf("\n!!! ERRO AO ABRIR ARQUIVO !!!");
        return 1;
    }

    if(arq_ordenado == NULL){
        printf("\n!!! ERRO AO ABRIR ARQUIVO !!!");
        return 1;
    }

    do{
        printf("\n               ___ MENU ___\n");
        printf("\n[1] - Criar Base de Dados\n[2] - Procurar Funcionario por KEY_SORTING");
        printf("\n[3] - Procurar funcionario por INSERTION_SORT\n[4] - Procurar funcionario por BUSCA_SEQUENCIAL\n");
        printf("[5] - Imprimir base de dados completa\n[0] - Sair\n");
        
        printf("\nDigite a opcao desejada: ");
        scanf("%i", &condicao);
        
        switch(condicao){
            case 1:
                printf("\nQuantos funcionarios serao inseridos na base de dados? _ ");
                scanf("%i", &qtd_de_Func);
                cria_base_de_dados(arq, qtd_de_Func);   //Cria uma database no arquivo com funcionarios de códigos aleatórios
                cria_base_de_dados(arq_ins, qtd_de_Func);
                printf("\n*** Base de dados criada com sucesso\n");
                baseid ++;
                break;
            case 2: 
                if(baseid == 0){
                    printf("\n!!! E necessario criar uma base de dados antes de buscar por um funcionario !!!\n");
                    break;
                }
                arq_ord_id ++;
                printf("\nDigite o codigo do funcionario que deseja buscar: _ ");
                scanf("%i", &find_func);
                Key_sorting_file(arq, arq_ordenado, qtd_de_Func); //Key_sorting é chamada recebendo o arquivo desordenado dados_KEY.dat, o arquivo vazio dados_ordenados.dat e a quantidade de funcionarios cadastrados. Ao fim da execução teremos o arquivo dados_ordenados.dat preenchido ordenadamente

                start_time_bin = clock(); //Início da contagem do tempo de execução da busca sequencial
                func = buscaBinaria(find_func, qtd_de_Func, arq_ordenado, &tot_comp_bin);
                end_time_bin = clock(); //Término da contagem do tempo de execução da busca binaria

                temp_exe_bin += (double)(end_time_bin-start_time_bin)/CLOCKS_PER_SEC;//Cálculo do tempo de execução da busca binaria
    
                printf("\n\n________ ## Teste utilizando a Busca Binaria (KEY_SORTING) ## ________\n\n");
                if(func == NULL){
                    printf("Funcionario inexistente na base de dados\n");
                    printf("______________________________________________________________________\n\n");
                }else{
                    printf("Funcionario encontrado: Imprimindo...");
                    toString(func);
                }
                printf("\n## No de comparacoes da busca Binaria: %i", tot_comp_bin);
                printf("\n## Tempo gasto na Execucao da busca Binaria: %.6f s\n", temp_exe_bin);
                printf("______________________________________________________________________\n\n");

                break;
            case 3:
                if(baseid == 0){
                    printf("\n!!! E necessario criar uma base de dados antes de buscar por um funcionario !!!\n");
                    break;
                }
                printf("\nDigite o codigo do funcionario que deseja buscar: _ ");
                scanf("%i", &find_func);

                insertion_sort_disco(arq_ins, qtd_de_Func);

                start_time_bin = clock(); //Início da contagem do tempo de execução da busca binaria
                func = buscaBinaria(find_func, qtd_de_Func, arq_ins, &tot_comp_bin);
                end_time_bin = clock(); //Término da contagem do tempo de execução da busca binaria

                temp_exe_bin += (double)(end_time_bin-start_time_bin)/CLOCKS_PER_SEC; //Cálculo do tempo de execução da busca binaria
                
                printf("\n\n________ ## Teste utilizando a Busca Binaria (INSERTION_SORTING) ## ________\n\n");
                if(func == NULL){
                    printf("Funcionario inexistente na base de dados\n");
                    printf("____________________________________________________________________________\n\n");
                }else{
                    printf("Funcionario encontrado: Imprimindo...");
                    toString(func);
                }
                printf("\n## No de comparacoes da busca Binaria: %i", tot_comp_bin);
                printf("\n## Tempo gasto na Execucao da busca Binaria: %.6f s\n", temp_exe_bin);
                printf("____________________________________________________________________________\n\n");

                break;
            case 4:
                if(baseid == 0){
                    printf("\n!!! E necessario criar uma base de dados antes de buscar por um funcionario !!!\n");
                    break;
                }
                printf("\nDigite o codigo do funcionario que deseja buscar: _ ");
                scanf("%i", &find_func);
                start_time_seq = clock(); //Início da contagem do tempo de execução da busca sequencial
                func = busca_sequencial(find_func, arq, qtd_de_Func, &tot_comp_seq);
                end_time_seq = clock(); //Término da contagem do tempo de execução da busca sequencial

                temp_exe_seq += (double)(end_time_seq-start_time_seq)/CLOCKS_PER_SEC; //Cálculo do tempo de execução da busca sequencial

                printf("\n\n________ ## Teste utilizando a Busca Sequencial ## ________\n\n");
                if(func == NULL){
                    printf("!!! Funcionario inexistente na base de dados\n");
                     printf("\n                 ##### Observacao #####\n\nO Codigo dos funcionarios eh gerado de forma aleatoria\ntente executar novamente ou usar outro codigo\n");
                    printf("____________________________________________________________\n\n");
                    break;
                }else{
                    printf("Funcionario encontrado: Imprimindo...");
                    toString(func);
                }
                printf("\n## No de comparacoes da busca sequencial: %i",tot_comp_seq);
                printf("\n## Tempo gasto na Execucao da busca sequencial: %.6f s\n", temp_exe_seq);
                printf("____________________________________________________________\n\n");
                break;
            case 5:
                if(baseid == 0){
                    printf("\n!!! E necessario criar uma base de dados antes de imprimi-la !!!\n");
                    break;
                }
                int cond_bd;
                printf("\nPara imprimir a base de dados ORDENADA tecle [1]\nPara imprimir a base de dados DESORDENADA tecle [2]\nopcao: _ ");
                scanf("%i", &cond_bd);
                if(cond_bd == 1){
                    if(arq_ord_id != 0){
                        for(int i=0; i<qtd_de_Func; i++){
                            fseek(arq_ordenado, i*sizeof(TFunc), SEEK_SET);
                            func = le(arq_ordenado);
                            toString(func);
                        }
                    }else{
                        printf("\n!!! E necessario realizar o Key sorting antes de imprimir os dados ordenados !!!\n");
                    }
                }else if(cond_bd == 2){
                    for(int i=0; i<qtd_de_Func; i++){
                        fseek(arq, i*sizeof(TFunc), SEEK_SET);
                        func = le(arq);
                        toString(func);
                    }
                }else{
                    printf("\n!!! Opcao invalida, tente novamente !!!\n");
                    break;
                }
                break;
            case 0:
                printf("\n## Obrigado por usar este programa :) ##\n");
                break;
            default:
                printf("\n !!! Opacao invalida, tente novamente !!!\n");
                break;
        }
    }while(condicao!= 0);

    free(func);
    fclose(arq);
    fclose(arq_ordenado);
    fclose(arq_ins);

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

void salva_arq(TFunc *func, FILE *arq){
    
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

    int booleanVerify[nFunc];   // 0 = false   1 = true
    for(int i=0; i<nFunc; i++){
        booleanVerify[i] = 0;
    }

    srand(time(NULL));

    for(int i=1; i<= nFunc; i++){

        int rand_num =rand() % nFunc;

        if(booleanVerify[rand_num] == 0){

            TFunc func;

            func.cod = rand_num;
            sprintf(func.nome, "Funcionario %i", rand_num);
            sprintf(func.cpf, "000.000.000-00");
            sprintf(func.data_nascimento, "01/01/2000");
            func.salario = 1000 + rand_num;
            fseek(arq, (i-1)*sizeof(TFunc), SEEK_SET);
            salva_arq(&func, arq);

            booleanVerify[rand_num] = 1;

        }else{
            i--;
        }
    }
}

TFunc *busca_sequencial(int cod, FILE *arq, int tam_arq, int *comp){

    for(int i=0; i<tam_arq; i++){
        *comp +=1;
        fseek(arq, i*sizeof(TFunc), SEEK_SET);
        TFunc *func = le(arq);
        if(func->cod == cod){
            return func;
        }
    }

    return NULL;

}

TFunc *buscaBinaria (int cod, int qtd_func, FILE *arq, int *comp){

    int l = 0, r = qtd_func-1; // l = left / r = right

    while(l <= r){

        *comp +=1;
        int meio = (l+r)/2;

        fseek(arq, meio*sizeof(TFunc), SEEK_SET);
        TFunc *func = le(arq);

        if(cod == func->cod){
            return func;
        }else if(func->cod < cod){
            l = meio+1;
        }else{
            r = meio-1;
        }
    }
    return NULL;
}

void ordena_array(Key_sorting *array, int qtd_func){

    for (int i=0; i< qtd_func; i++) {
        for (int j=i+1; j< qtd_func; j++) {
            if (array[i].cod > array[j].cod) {
                
                Key_sorting aux = array[i];
                array[i] = array[j];
                array[j] = aux;

            }
        }
    }
}

void Key_sorting_file(FILE *arq, FILE *arq_ordenado, int qtd_func){

    printf("\nRealizando Key Sorting ... \n");

    clock_t start_time, end_time;
    double temp_exe = 0.0;

    start_time = clock();

    Key_sorting tag_array[qtd_func];

    rewind(arq);

    for(int i=0; i<qtd_func; i++){
        fseek(arq, i*sizeof(TFunc), SEEK_SET);
        tag_array[i].RRN = ftell(arq);
        TFunc *func = le(arq); 
        tag_array[i].cod = func->cod;
    }

    ordena_array(&tag_array, qtd_func);

    rewind(arq);

    for(int i=0; i<qtd_func; i++){

        fseek(arq,tag_array[i].RRN, SEEK_SET);
        TFunc *func = le(arq);

        fseek(arq_ordenado, i*sizeof(TFunc), SEEK_SET);
        salva_arq(func, arq_ordenado);
    }

    end_time = clock();

    temp_exe += (double)(end_time-start_time)/CLOCKS_PER_SEC;
    printf("\n## Tempo gasto na Execucao do Key Sorting: %.8f s\n", temp_exe);

}


void insertion_sort_disco(FILE *arq, int qtd_func){
    clock_t start_time, end_time;
    double temp_exe = 0.0;
    start_time = clock();

    printf("\nRealizando Insertion sort ... \n");
    rewind(arq); 
    int i;
    for (int j = 2; j <= qtd_func; j++) {
        fseek(arq, (j-1) * sizeof(TFunc), SEEK_SET);
        TFunc *func_j = le(arq);
        i = j - 1;
        fseek(arq, (i-1) * sizeof(TFunc), SEEK_SET);
        TFunc *func_i = le(arq);
        while ((i > 0) && (func_i->cod > func_j->cod)) {
            fseek(arq, i * sizeof(TFunc), SEEK_SET);
            salva_arq(func_i, arq);
            i = i - 1;
            fseek(arq, (i-1) * sizeof(TFunc), SEEK_SET);
            func_i = le(arq);
         }
        fseek(arq, (i) * sizeof(TFunc), SEEK_SET);
        salva_arq(func_j, arq);
    }
    fflush(arq);

    end_time = clock();
    temp_exe += (double)(end_time-start_time)/CLOCKS_PER_SEC;
    printf("\n## Tempo gasto na Execucao do Insertion Sorting: %.8f s\n", temp_exe);
}

// Anotações


    // start_time_seq = clock(); //Início da contagem do tempo de execução da busca sequencial
    // TFunc *func = busca_sequencial(find_func, arq, qtd_de_Func, &tot_comp_seq);
    // end_time_seq = clock(); //Término da contagem do tempo de execução da busca sequencial
    
    // temp_exe_seq += (double)(end_time_seq-start_time_seq)/CLOCKS_PER_SEC; //Cálculo do tempo de execução da busca sequencial
    
    // printf("________ ## Teste utilizando a Busca Sequencial ## ________\n\n");
    // if(func == NULL){
    //     printf("!!! Funcionario inexistente na base de dados\n");
    //     printf("\n                 ##### Observacao #####\n\nO Codigo dos funcionarios eh gerado de forma aleatoria\ntente executar novamente ou usar outro codigo\n");
    //     printf("____________________________________________________________\n\n");
    //     return 1;
    // }else{
    //     printf("Funcionario encontrado: Imprimindo...");
    //     toString(func);
    // }

    // printf("\n## No de comparacoes da busca sequencial: %i",tot_comp_seq);
    // printf("\n## Tempo gasto na Execucao da busca sequencial: %.6f s\n", temp_exe_seq);
    // printf("____________________________________________________________\n\n");

    // Key_sorting_file(arq, arq_ordenado, qtd_de_Func); //Key_sorting é chamada recebendo o arquivo desordenado dados_KEY.dat, o arquivo vazio dados_ordenados.dat e a quantidade de funcionarios cadastrados. Ao fim da execução teremos o arquivo dados_ordenados.dat preenchido ordenadamente

    // start_time_bin = clock(); //Início da contagem do tempo de execução da busca sequencial
    // func = buscaBinaria(find_func, qtd_de_Func, arq_ordenado, &tot_comp_bin);
    // end_time_bin = clock(); //Término da contagem do tempo de execução da busca binaria

    // temp_exe_bin += (double)(end_time_bin-start_time_bin)/CLOCKS_PER_SEC;//Cálculo do tempo de execução da busca binaria
    
    // printf("\n\n________ ## Teste utilizando a Busca Binaria ## ________\n\n");
    // if(func == NULL){
    //     printf("Funcionario inexistente na base de dados\n");
    //     printf("____________________________________________________________\n\n");
    //     return 1;
    // }else{
    //     printf("Funcionario encontrado: Imprimindo...");
    //     toString(func);
    // }
    // printf("\n## No de comparacoes da busca Binaria: %i", tot_comp_bin);
    // printf("\n## Tempo gasto na Execucao da busca Binaria: %.6f s\n", temp_exe_bin);
    // printf("____________________________________________________________\n\n");

    // printf("Deseja imprimir a Base de dados completa? (s ou n): ");
    // char cond = getchar();

    // if(cond == 's' || cond == 'S'){
    //     for(int i=0; i<qtd_de_Func; i++){
    //         fseek(arq_ordenado, i*sizeof(TFunc), SEEK_SET);
    //         func = le(arq_ordenado);
    //         toString(func);
    //     }
    // }
