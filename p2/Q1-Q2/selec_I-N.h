#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "src/funcionarios.h"

typedef struct{
    TFunc *func;
    int is_frozen // 0 -> false ; 1 -> true
}TPart;

void selection_sub_aux(FILE *arq, char* nome, TPart* part, int ord);
void selection_sub(FILE *arq, int ord);
void selection_nat_aux();
void selection_nat();