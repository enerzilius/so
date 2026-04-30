#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição:  programa que lê uma expressão matemática simples (+, -, *, /) e passe para outro
programa que realiza o cálculo e devolve a resposta - usando fifo
 * Data de criação: 29/04/2026
 * Data de modificação: 29/04/2026
 */

#define SERVER_FIFO "/tmp/serverfifo"

int calcular(int num1, int num2, char op);

int main(int argc, char *argv[]) {
  char str[51];

  int fd_server;

  // criando o fifo
  if ((mkfifo(SERVER_FIFO, 0664) == -1) && (errno != EEXIST)) {
    perror("mkfifo");
    return EXIT_FAILURE;
  }

  // criando processo filho para não ter que fazer em dois arquivos diferentes
  pid_t pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Falha no fork.\n");
    return EXIT_FAILURE;
  }

  // processo pai, lê string do usuário e usa o fifo para enviar
  if (pid != 0) {
    // abre o FIFO para escrita
    if ((fd_server = open(SERVER_FIFO, O_WRONLY)) == -1) {
      perror("open");
    }

    printf("Digite um cálculo simples (+, -, *, /) escrito como a + b : ");
    scanf("%50[^\n]", str);

    write(fd_server, str, strlen(str));

    if (close(fd_server) == -1) {
      perror("close error:server fifo");
      return EXIT_FAILURE;
    }

    wait(NULL);
    return EXIT_SUCCESS;
  } else {
    // processo filho, lê os dados salvos pelo outro processo, calcula e imprime

    // abre o FIFO para escrita
    if ((fd_server = open(SERVER_FIFO, O_RDONLY)) == -1) {
      perror("open");
    }

    // lê e trata mensagens do FIFO
    memset(str, '\0', sizeof(str));
    int numBytesRead = read(fd_server, str, sizeof(str));
    switch (numBytesRead) {
    case -1:
      perror("Erro na leitura");
      break;
    case 0:
      printf("Sem dados\n");
      close(fd_server);
      fd_server = open(SERVER_FIFO, O_RDONLY);
      break;
    default:
      printf("Recebeu %d bytes: %s\n", numBytesRead, str);
    }

    // processa o que foi passado pela pipe:
    // divide em um vetor e traduz para números e oparador em char
    char* arguments[4];
    char* temp = str;

    for (int i = 0; i < 3 && (arguments[i] = strsep(&temp, " ")) != NULL; ++i); 
    free(temp);
    arguments[3] = (char*)0;

    int num1 = atoi(arguments[0]);
    char operador = arguments[1][0];
    int num2 = atoi(arguments[2]);

    // verifica se a operação é válida
    if(operador != '+' && operador != '-' && operador != '*' && operador != '/') {
        printf("operação não permitida.");
        return EXIT_FAILURE;
    }

    int resultado = calcular(num1, num2, operador);

    printf("%d %c %d = %d\n", num1, operador, num2, resultado);
    
    fflush(stdout);
    return EXIT_SUCCESS;
  }
}

// realiza o cálculo simples usando um switch para saber qual fazer
int calcular(int num1, int num2, char op) {
    switch (op)
    {
        case '+':
            return num1 + num2;
        case '-':
            return num1-num2;
        case '*':
            return num1*num2;
        case '/':
            return num1/num2;
        default:
            return 0;
    }
}