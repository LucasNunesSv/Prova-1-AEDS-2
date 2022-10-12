# Trabalho Prático da disciplina de AEDS 2 - CSI-429
# Repositório destinado a implementação das Provas 1 , 2 e 3 da disciplina

Professora: Tatiana Alves Costa  --  Valor: 20 pontos

Integrantes:

* Lucas Nunes Silveira - M 20.2.8040
* Matheus Lopes Moreira - M 20.2.8002

(Prova 1){

1) (5 pontos) Dada a estrutura de dados Funcionário definida em aula, pede-se:

a) (5 pontos) Crie uma base de dados contendo 100 registros de funcionários, armazenados em
um arquivo binário.

b) (5 pontos) Realize uma busca sequencial por um funcionário específico. Considerar como
chave de busca o código do funcionário. Informe o total de comparações feitas até encontrar o
funcionário em questão, bem como o tempo gasto na busca.

c) (5 pontos) Utilize o método de ordenação KeySorting para ordenar o arquivo contendo a base
de dados. Informe tempo na ordenação.

d) (5 pontos) Realize a busca pelo mesmo funcionário escolhido na letra b. Utilize agora a busca
binária no arquivo ordenado. Informe o total de comparações feitas até encontrar o funcionário
em questão, bem como o tempo gasto na busca.

__Considerações: 

1. A função cria_base_de_dados() cria um arquivo binario (.dat) contendo a quantidade de funcionarios
que foi indicada ao inicio do programa, os códigos dos funcionarios são gerados de forma aleatório pela
função rand(). Portanto, pode ocorrer casos que buscamos por um código que não esta contido da base de dados
pois provavelmente a função rand() nao criou um funcionario com o numero que desejamos buscar, neste caso peço que
execute o programa novamente ou mude o código que deseja buscar

2. O arquivo funcionarios_KEY.c refere-se ao programa que utiliza a implementação do metodo de ordenação KEYSORTING
(solicitado na prova 1), que irá gerar dois arquivos binarios(.dat) sendo eles: 

- dados_INS.dat , base de dados contendo os dados DESORDENADOS dos funcionarios 
- dados_ordenados.dat, outra base de dados resultante da função de ordenação key_sorting, que armazena os mesmos dados da base antiga porém de forma ordenada tendo como fator de ordenação (KEY) o código dos funcionarios

3. O arquivo funcionarios_INS.c refere-se ao programa que utiliza a implementação do metodo de ordenação INSERTIONSORT (ponto extra), que irá gerar um arquivo binario (.dat) que armazena os dados dos funcionarios inicialmente de forma desordenada, após a chamada da função insertionsort() que ordenará o arquivo internamente, teremos o mesmo arquivo porém ordenado com base no fator de ordenação que seria o código do funcionario.

}

(Prova 2){

Questão 1) (5 pontos) Implementar o método Seleção com Substituição para gerar partições
classificadas. Testar o método utilizando a base de dados criada para a Prova 01. Assumir que
na memória cabem 6 registros simultaneamente.

Questão 2) (5 pontos) Implementar o método Seleção Natural para gerar partições
classificadas. Testar o método utilizando a base de dados criada para a Prova 01. Assumir que
na memória cabem 6 registros simultaneamente. Tamanho do reservatório = 6

__Considerações: 

1. A execução da prova 2 depende exclusivamente do material que foi desenvolvido durante a prova 1. Portanto, 
optamos pela criação de um menu interativo que possue todas as funcionalidades que desenvolvemos durante todo o curso. 
O mesmo se aplica ao desenvolvimento da prova 3.

}
