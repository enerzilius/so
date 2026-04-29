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
 * Descrição:  lê strings digitadas pelo usuário e envia para outro programa que
recebe essas strings e exibe na tela: a string, o tamanho, o número de
consoantes, o número de vogais e o número de espaços usando fifo
 * Data de criação: 28/04/2026
 * Data de modificação: 29/04/2026
 */

#define SERVER_FIFO "/tmp/serverfifo"

void analisarString(char *str, int *nVogais, int *nConsoantes, int *nEspacos);

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

    printf("Digite algo para enviar: ");
    scanf("%50[^\n]", str);

    write(fd_server, str, strlen(str));

    if (close(fd_server) == -1) {
      perror("close error:server fifo");
      return EXIT_FAILURE;
    }

    wait(NULL);
    return EXIT_SUCCESS;
  } else {
    // processo filho, lê os dados salvos pelo outro processo na pipe, processa e imprime

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

    int numeroConsoantes = 0;
    int numeroVogais = 0;
    int numeroEspacos = 0;

    analisarString(str, &numeroVogais, &numeroConsoantes, &numeroEspacos);

    printf("String enviada: %s\n", str);
    printf("Tamanho da string: %ld\n", strlen(str));
    printf("Numero de vogais: %d\n", numeroVogais);
    printf("Numero de consoantes: %d\n", numeroConsoantes);
    printf("Numero de espaços: %d\n", numeroEspacos);
    fflush(stdout);
    return EXIT_SUCCESS;
  }
}

// faz a contagem das vogais e consoantes da string
void analisarString(char *str, int *nVogais, int *nConsoantes, int *nEspacos) {
  char c = str[0];
  int i = 0;
  while (c != 0) {
    char lower = tolower(c);

    if (c == ' ')
      (*nEspacos)++;
    if (lower >= 'a' && lower <= 'z') {
      if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' ||
          lower == 'u') {
        (*nVogais)++;
      } else {
        (*nConsoantes)++;
      }
    }

    c = str[++i];
  }
}
