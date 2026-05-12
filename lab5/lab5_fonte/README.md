# Como compilar

```bash
$ make
```

- O comando `make` vai compilar todos os programas. Para compilar um programa específico, basta usar `make <programa>`. A lista de programas pode ser vista no `Makefile`.

# Como executar
-  
```bash
$ ./1A_pipe.out
$ ./1A_fifo.out
$ ./1B_pipe.out
$ ./1B_fifo.out
$ ./2A.out <arquivo>
$ ./2B.out 
$ ./2C.out
$ ./3.out
$ ./4.out <número de elementos> <número de filhos>
```

# Bibliotecas usadas

- Além das padrões (`stdlib`, `stdio`) foram usadas as bibliotecas:
  - `ctype.h`
  - `errno.h`
  - `fcntl.h`
  - `string.h`
  - `sys/stat.h`
  - `sys/types.h`
  - `sys/wait.h`
  - `unistd.h`
  - `linux/limits.h`
  - `pwd.h`
  - `signal.h`
  - `time.h`
  - `sys/mman.h`
  - `sys/shm.h

# Exemplos de uso:
```bash
❯ make
gcc -Wall 1A_pipe.c -o 1A_pipe.out
gcc -Wall 1A_fifo.c -o 1A_fifo.out
gcc -Wall 1B_pipe.c -o 1B_pipe.out
gcc -Wall 1B_fifo.c -o 1B_fifo.out
gcc -Wall 2A.c -o 2A.out
gcc -Wall 2B.c -o 2B.out
gcc -Wall 2C.c -o 2C.out
gcc -Wall 3.c -o 3.out
gcc -Wall 4.c -o 4.out

✗ ./1B_pipe.out
Digite um cálculo simples (+, -, *, /) escrito como a + b : 10 + 1
10 + 1 = 11

❯ ./2B.out
PID: 81329
^C
-- Sinal de término recebido: terminando de salvar informações.
Todos resultados salvos em 'output.txt'

❯ ./3.out
Processo pai (82975): producer
Processo filho (82976) consumiu:
Título: titulo do livro
Autor: autor do livro
Número de páginas: 67

✗ ./4.out 20 2
19 7 10 17 13 30 30 18 8 19 31 16 15 24 25 22 2 21 38 18
```

