#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "arvoreb.h"
#include "src/funcionarios.h"

// Lucas Nunes Silveira - 20.2.8040
// Matheus Lopes Moreira - 20.2.8002

void init(Tpointer *tree){
    *tree = NULL;
}

void inOrder(Tpointer tree){

    int i;

    if(tree != NULL){
        for(i=0; i<tree->qtd_registros; i++){
            inOrder(tree->pointer[i]);
            printf("%ld ", tree->Rfunc[i].cod);
        }
        inOrder(tree->pointer[i]);
    }
    return;
}

void search(TFunc *func, Tpointer pointer){
    long i=1;
    if(pointer == NULL){
        printf("\n!! Este Registro nao esta presente na arvore!!\n");
        return;
    }

    while(i < pointer->qtd_registros && func->cod > pointer->Rfunc[i-1].cod) i++;

    if(func->cod == pointer->Rfunc[i-1].cod){
        *func = pointer->Rfunc[i-1];
        return;
    }

    if(func->cod < pointer->Rfunc[i-1].cod){
        search(func, pointer->pointer[i]);
    }
}

void pageInsert(Tpointer pointer, TFunc func, Tpointer rightPointer){
    short notFound;
    int k;

    k = pointer->qtd_registros;
    notFound = (k > 0);
    while(notFound){
        if(func.cod >= pointer->Rfunc[k-1].cod){
            notFound = FALSE;
            break;
        }

        pointer->Rfunc[k] = pointer->Rfunc[k-1];
        pointer->pointer[k+1] = pointer->pointer[k];
        k--;
        if(k < 1) notFound = FALSE;
    }
    pointer->Rfunc[k] = func;
    pointer->pointer[k+1] = rightPointer;
    pointer->qtd_registros++;
}

void ins(TFunc func, Tpointer pointer, short *up, TFunc *funcReturn, Tpointer *pointerReturn){
    long i = 1, j;
    Tpointer apTemp;

    if(pointer == NULL){
        *up = TRUE;
        (*funcReturn) = func;
        (*pointerReturn) = NULL;
        return;
    }

    while(i < pointer->qtd_registros && func.cod > pointer->Rfunc[i-1].cod) i++;

    if(func.cod == pointer->Rfunc[i-1].cod){
        printf("\n!! [ERRO] - Registro ja esta presente !!\n");
        *up = FALSE;
        return;
    }

    if(func.cod < pointer->Rfunc[i-1].cod) i--;

    ins(func, pointer->pointer[i], up, funcReturn, pointerReturn);

    if(!*up) return;

    if(pointer->qtd_registros < MM){
        pageInsert(pointer, *funcReturn, *pointerReturn);
        *up = FALSE;
        return;
    }

    apTemp = (Tpointer)malloc(sizeof(Tpag));
    apTemp->qtd_registros = 0;
    apTemp->pointer[0] = NULL;
    if(i < M + 1){
        pageInsert(apTemp, pointer->Rfunc[MM-1], pointer->pointer[MM]);
        pointer->qtd_registros--;
        pageInsert(pointer, *funcReturn, *pointerReturn);
    }else{
        pageInsert(apTemp, *funcReturn, *pointerReturn);
    }

    for(j = M + 2; j <= MM; j++){
        pageInsert(apTemp, pointer->Rfunc[j-1], pointer->pointer[j]);
    }
    pointer->qtd_registros = M; apTemp->pointer[0] = pointer->pointer[M+1];
    *funcReturn = pointer->Rfunc[M]; *pointerReturn = apTemp;
}

void insert(TFunc func, Tpointer *tree){
    short up;
    TFunc funcReturn;
    Tpag *pointerReturn, *apTemp;
    ins(func, *tree, &up, &funcReturn, &pointerReturn);
    if(up){
        apTemp = (Tpag *)malloc(sizeof(Tpag));
        apTemp->qtd_registros = 1;
        apTemp->Rfunc[0] = funcReturn;
        apTemp->pointer[1] = pointerReturn;
        apTemp->pointer[0] = *tree;
        *tree = apTemp;
    }
}
void reconstitui(Tpointer ApPag, Tpointer ApPai, int PosPai, short *down);
void antecessor(Tpointer Ap, int Ind, Tpointer ApPai, short *down);
void ret(int funcCod, Tpointer *pointer, short *down);
void remove(int funcCod, Tpointer *pointer);
