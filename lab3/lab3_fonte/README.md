# Como compilar

```bash
$ make
```

- O comando `make` vai compilar todos os programas. Para compilar um programa específico, basta usar `make <programa>`. A lista de programas pode ser vista no `Makefile`.

# Como executar

```bash
$ ./busca.out <Número de elementos no vetor> <Número de threads>
$ ./processar_matriz.out <Número de threads> <Número de linhas> <Número de Colunas>
```

- Se deixar só o número de linhas no comando `./processar_matriz.out`, esse número também vai ser usado para as colunas

# Bibliotecas usadas

- Além das padrões (`stdlib`, `stdio`) foram usadas as bibliotecas:
  - `time.h`
  - `pthread.h`
  - `math.h`

# Exemplos de uso:
```bash
$ make
gcc busca.c -o busca.out
gcc -o processar_matriz.out matriz.o processar_matriz.o -lm

$ ./busca.out 20 2 
Gerando vetor...
1 19 15 7 12 15 16 17 4 12 16 3 0 3 18 13 12 5 18 8
Elemento a ser encontrado: 12
139936348219072 encontrou o número 12 na posicição 4.
139936348219072 encontrou o número 12 na posicição 9.
139936331437760 encontrou o número 12 na posicição 16.
```

