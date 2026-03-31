# Como compilar

```bash
$ make
```

- O comando `make` vai compilar todos os programas. Para compilar um programa específico, basta usar `make <programa>`. A lista de programas pode ser vista no `Makefile`.
- O arquivo `forkbomb.c` vai gerar avisos ao ser compilado.

# Como executar

```bash
$ ./hierarquia.out <Número de camadas>
$ ./exec.out <comando desejado>
$ ./busca_vetor.out <numero de elementos do vetor> <numero de filhos>
$ ./shell.out
```

# Bibliotecas usadas

- Além das padrões (`stdlib`, `stdio`) foram usadas as bibliotecas:
- - `unistd.h`
- - `time.h`
- - `sys/wait.h`
- - `sys/types.h`

# Exemplos de uso: 
```bash
$ make
gcc -Wall forkbomb.c -o forkbomb.out
forkbomb.c: In function ‘recursiveForks’:
forkbomb.c:6:6: warning: infinite recursion detected [-Winfinite-recursion]
    6 | void recursiveForks() {
      |      ^~~~~~~~~~~~~~
forkbomb.c:9:3: note: recursive call
    9 |   recursiveForks();
      |   ^~~~~~~~~~~~~~~~
gcc -Wall hierarquia.c -o hierarquia.out
gcc -Wall exec.c -o exec.out
gcc -Wall busca_vetor.c -o busca_vetor.out
gcc -Wall shell.c -o shell.out

$ busca_vetor.out 10 2
1 3 9 8 4 0 6 4 0 1
Elemento a ser encontrado: 4
Processo 22336 encontrou 4
Processo 22337 encontrou 4

$ ./exec.out ls
 busca_vetor.c                         exec.c       forkbomb.out    'Laboratorio 02 - processos.pdf'   shell.c
 busca_vetor.out                       exec.out     hierarquia.c     Makefile                          shell.out
 comandos_linux-sistema_processo.txt   forkbomb.c   hierarquia.out   README.md
Processo 126783 foi finalizado com estado 0.
```

