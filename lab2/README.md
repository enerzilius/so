# Como compilar

```bash
$ make
```

- O comando `make` vai compilar todos os programas. Para compilar um programa específico, basta usar `make <programa>`. A lista de programas pode ser vista no `Makefile`.
- O arquivo `forkbomb.c` vai gerar avisos ao ser compilado.

# Como executar

```bash
$ ./<programa>.out
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

$ ./busca_vetor.out 15 5
1605424241 1650560312 1557003612 981488601 1919060598 1854308327 1721319865 37229818 1407479294 1117422544 1096310109 1150086374 23209194 99630586 1221653730
Elemento a ser encontrado: 1919060598
Processo 122454 encontrou 1919060598
```

