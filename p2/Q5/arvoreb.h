#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "src/funcionarios.h"

#define M 2 //Ordem da arvore
#define MM (M*2)
#define FALSE 0
#define TRUE 1

typedef struct Tpag* Tpointer;
typedef struct Tpag {
    short qtd_registros; //quantidade de chaves armazenadas no nó
    TFunc Rfunc[MM]; //array de registros
    Tpointer pointer[MM + 1];
} Tpag;

void init(Tpointer *tree);
void inOrder(Tpointer tree);
void search(TFunc *func, Tpointer pointer);
void pageInsert(Tpointer pointer, TFunc func, Tpointer rightPointer);
void ins(TFunc func, Tpointer pointer, short *up, TFunc *funcReturn, Tpointer *pointerReturn);
void insert(TFunc func, Tpointer *tree);
void reconstitui(Tpointer ApPag, Tpointer ApPai, int PosPai, short *down);
void antecessor(Tpointer Ap, int Ind, Tpointer ApPai, short *down);
void ret(int funcCod, Tpointer *pointer, short *down);
void remove(int funcCod, Tpointer *pointer);