#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcionarios.h"

int main(){

    FILE *arq = fopen("dados.dat", "wb+");
    if(arq == NULL){
        printf("\n!!! ERRO AO ABRIR ARQUIVO !!!");
        return 1;
    }
    
    int nFunc = 100;
    cria_base_de_dados(arq, nFunc);
    clock_t start_time, end_time;
    double temp_exe = 0.0;

    start_time = clock();
    TFunc *func = busca_sequencial(1, arq, nFunc);
    end_time = clock();
    
    //float temp_exe = (((float)end_time - (float)start_time) / 1000000.0f);
    temp_exe += (double)(end_time-start_time)/CLOCKS_PER_SEC;
    

    if(func == NULL){
        printf("Funcionario inexistente na base de dados");
    }else{
        printf("Funcionario encontrado: Imprimindo...\n");
        toString(func);
    }

    printf("\n\n## No de comparacoes: %i", func->qtd_comparacoes);
    printf("\n## Tempo gasto na Execucao da busca: %lf s\n\n", temp_exe);
  
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

/*
KEYSORTING 
Método:
• 1. Leia o arquivo e coloque num vetor de tags a chave e a RRN de 
cada registro.
• 2. Ordene o vetor em memória (“Internal Sorting”)
• 3. Reescrever os arquivo segundo a ordem dada pelo vetor ordenado
*/

/* ____ CHATZIN ____

Deu certo KADSASDASDK
xove qq ce arrumou 
no stack overflow ? isso sdsdslkdks
KKKKKKKKKKK, fazzer o insertsort? vou tentar fazer e deixar de comentario no codigo, vai que farmo ponto ne KKK
KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK pqpm KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK
EUY 
to tentando entender, isso ai é o timer ?
 SKDKSKSSDK
 tem no stack

 VEYY 
 nao tem a prova
 ela pediu busca SEQUENCIAL AAAAA
 E A GNT QUEBRANDO A CABEÇA
 COM BINARIA TMNC
 
 



 CHEGOU UMA GALERA AQUI, JA VOLTO.; 
 blz KASKASKDAS

 VOLTEI 
 

esse clock é da time.h ?
doidera
xove se entendi, busca sequencial pra indicar quantas comparações foram feitas né, então é literal usar o I de busca, ou tu ja fez isso ?]

b) (5 pontos) Realize uma busca sequencial por um funcionário específico. Considerar como
chave de busca o código do funcionário. Informe o total de comparações feitas até encontrar o
funcionário em questão, bem como o tempo gasto na busca.
então se começa do 0 e vai até o 12, teve 13 comparações
creio q sim KDKS ta errado?
na vdd
ele começa do 1 msm
se ja faz ta ok entãom sa
ce transformou em tad o projeto, pqp KKKK,
queeee
como assim?
uai mano, sabe o que é tad ?
é o .h ali, antes n tava estruturado dessa forma
zeca tatu

vdd DSKDKSD mas eh do video q ela postou
to seguindo so
essa .h eh so pra separar os escopos e o TAD ksdkd dava pra fazer tudo no main
mas assim fica mais separado
assim fica chatom n gosto, mas fé
ODEIO TADm funciona totalemnte diferente de classificação em outras linguagens, c tem esses frufrus esquisitos
KKKKKKKKKKKKKKKKK
scr

uma coisa q nao consegui fazer 
foi criar o main em outro arquivo
tipo queria criar um main.c q teria so a parte executavel, sem as funções
mas deu nao

so funciona se  tiver dentro da funcionarios.c
ai vc ta querendo frufruzar mais tbm né, é so fazer o que programa pede po KKKKKKKK ta maluco

KDASDKASASDKSD eu sou uma flor, por isso
queria procurar uma função pronta pra achar de base, mas to procurando e n ta vindo KKK
KSDKF triste
o slide dela n tem codigo, eh so abstração
eu n faço ideia de como faz a letra C
 
 reclamaram muito dela na ultimo periodo inclusive pr conta disso, so usa pseudolinguagem, n usava linguagem alegit, ai ninguem sabia implementar KKKK

Ah pronto, tava bom demais

legit , nesse link aqui tem https://stackoverflow.com/questions/18820288/sorting-based-on-key-from-a-file

KRL BROTHER N ACHO NADA DE KEYSORTING, so tem literal essa merda ai, desgraça de c
KKSDKDFKD eu ja nem sei mais oq fazer
tbm n, vou ter que dar uma saida, mais tarde volto
blzz
*/
