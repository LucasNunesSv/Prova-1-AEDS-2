
#include "headers/funcionarios.h"

void toString(TFunc *func)
{

    printf("\n\nNome: %s", func->nome);
    printf("\nCPF: %s", func->cpf);
    printf("\nCodigo: %i", func->cod);
    printf("\nData de nascimento: %s", func->data_nascimento);
    printf("\nSalario: %.2f", func->salario);
    printf("\n");
}

void salva_arq(TFunc *func, FILE *arq)
{

    fwrite(&func->cod, sizeof(int), 1, arq);
    fwrite(func->nome, sizeof(char), sizeof(func->nome), arq);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), arq);
    fwrite(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), arq);
    fwrite(&func->salario, sizeof(float), 1, arq);
}

TFunc *le(FILE *in)
{

    TFunc *func = (TFunc *)malloc(sizeof(TFunc));

    if (0 >= fread(&func->cod, sizeof(int), 1, in))
    {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(float), 1, in);

    return func;
}

void cria_base_de_dados(FILE *arq, int nFunc)
{

    int booleanVerify[nFunc]; // 0 = false   1 = true
    for (int i = 0; i < nFunc; i++)
    {
        booleanVerify[i] = 0;
    }

    srand(time(NULL));

    for (int i = 1; i <= nFunc; i++)
    {

        int rand_num = rand() % nFunc;

        if (booleanVerify[rand_num] == 0)
        {

            TFunc func;

            func.cod = rand_num;
            sprintf(func.nome, "Funcionario %i", rand_num);
            sprintf(func.cpf, "000.000.000-00");
            sprintf(func.data_nascimento, "01/01/2000");
            func.salario = 1000 + rand_num;
            fseek(arq, (i - 1) * sizeof(TFunc), SEEK_SET);
            salva_arq(&func, arq);

            booleanVerify[rand_num] = 1;
        }
        else
        {
            i--;
        }
    }
}

TFunc *busca_sequencial(int cod, FILE *arq, int tam_arq, int *comp)
{

    for (int i = 0; i < tam_arq; i++)
    {
        *comp += 1;
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        TFunc *func = le(arq);
        if (func->cod == cod)
        {
            return func;
        }
    }

    return NULL;
}

TFunc *buscaBinaria(int cod, int qtd_func, FILE *arq, int *comp)
{

    int l = 0, r = qtd_func - 1; // l = left / r = right

    while (l <= r)
    {

        *comp += 1;
        int meio = (l + r) / 2;

        fseek(arq, meio * sizeof(TFunc), SEEK_SET);
        TFunc *func = le(arq);

        if (cod == func->cod)
        {
            return func;
        }
        else if (func->cod < cod)
        {
            l = meio + 1;
        }
        else
        {
            r = meio - 1;
        }
    }
    return NULL;
}

void insertion_sort_disco(FILE *arq, int qtd_func)
{
    clock_t start_time, end_time;
    double temp_exe = 0.0;
    start_time = clock();

    printf("\nRealizando Insertion sort ... \n");
    rewind(arq);
    int i;
    for (int j = 2; j <= qtd_func; j++)
    {
        fseek(arq, (j - 1) * sizeof(TFunc), SEEK_SET);
        TFunc *func_j = le(arq);
        i = j - 1;
        fseek(arq, (i - 1) * sizeof(TFunc), SEEK_SET);
        TFunc *func_i = le(arq);
        while ((i > 0) && (func_i->cod > func_j->cod))
        {
            fseek(arq, i * sizeof(TFunc), SEEK_SET);
            salva_arq(func_i, arq);
            i = i - 1;
            fseek(arq, (i - 1) * sizeof(TFunc), SEEK_SET);
            func_i = le(arq);
        }
        fseek(arq, (i) * sizeof(TFunc), SEEK_SET);
        salva_arq(func_j, arq);
    }
    fflush(arq);

    end_time = clock();
    temp_exe += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\n## Tempo gasto na Execucao do Insertion Sorting: %.8f s\n", temp_exe);
}

void Key_sorting_file(FILE *arq, FILE *arq_ordenado, int qtd_func)
{

    printf("\nRealizando Key Sorting ... \n");

    clock_t start_time, end_time;
    double temp_exe = 0.0;

    start_time = clock();

    Key_sorting tag_array[qtd_func];

    rewind(arq);

    for (int i = 0; i < qtd_func; i++)
    {
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        tag_array[i].RRN = ftell(arq);
        TFunc *func = le(arq);
        tag_array[i].cod = func->cod;
    }

    ordena_array(&tag_array, qtd_func);

    rewind(arq);

    for (int i = 0; i < qtd_func; i++)
    {

        fseek(arq, tag_array[i].RRN, SEEK_SET);
        TFunc *func = le(arq);

        fseek(arq_ordenado, i * sizeof(TFunc), SEEK_SET);
        salva_arq(func, arq_ordenado);
    }

    end_time = clock();

    temp_exe += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\n## Tempo gasto na Execucao do Key Sorting: %.8f s\n", temp_exe);
}

void ordena_array(Key_sorting *array, int qtd_func)
{

    for (int i = 0; i < qtd_func; i++)
    {
        for (int j = i + 1; j < qtd_func; j++)
        {
            if (array[i].cod > array[j].cod)
            {

                Key_sorting aux = array[i];
                array[i] = array[j];
                array[j] = aux;
            }
        }
    }
}

TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nasc, float salario)
{
    TFunc *funcionario = (TFunc *)malloc(sizeof(TFunc));
    if (funcionario)
        memset(funcionario, 0, sizeof(TFunc));
    funcionario->cod = cod;
    strcpy(funcionario->nome, nome);
    strcpy(funcionario->cpf, cpf);
    strcpy(funcionario->data_nascimento, data_nasc);
    funcionario->salario = salario;

    return funcionario;
}

int cmp_funcionario(TFunc *f1, TFunc *f2)
{
    if (f1 == NULL)
    {
        return (f2 == NULL);
    }
    if (f1->cod != f2->cod)
    {
        return 0;
    }
    if (strcmp(f1->cpf, f2->cpf) != 0)
    {
        return 0;
    }
    if (strcmp(f1->nome, f2->nome) != 0)
    {
        return 0;
    }
    if (strcmp(f1->data_nascimento, f2->data_nascimento) != 0)
    {
        return 0;
    }
    if (f1->salario != f2->salario)
    {
        return 0;
    }
    return 1;
}

void selec_sub();
void selec_nat();