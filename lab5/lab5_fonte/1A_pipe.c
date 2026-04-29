#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição:  lê strings digitadas pelo usuário e envia para outro programa que
recebe essas strings e exibe na tela: a string, o tamanho, o número de
consoantes, o número de vogais e o número de espaços usando pipe
 * Data de criação: 28/04/2026
 * Data de modificação: 29/04/2026
 */

void analisarString(char *str, int *nVogais, int *nConsoantes, int *nEspacos);

int main(int argc, char *argv[]) {
  char str[51];

  int myPipe[2];

  // Criar o pipe
  if (pipe(myPipe)) {
    fprintf(stderr, "Falha ao criar o Pipe.\n");
    return EXIT_FAILURE;
  }

  // criando processo filho
  pid_t pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Falha no fork.\n");
    return EXIT_FAILURE;
  }

  // processo pai, lê string do usuário e usa a pipe para enviar
  if (pid != 0) {
    close(myPipe[0]);
    printf("Digite algo para enviar: ");
    scanf("%50[^\n]", str);
    write(myPipe[1], str, sizeof(str));

    wait(NULL);
    return EXIT_SUCCESS;
  } else {
    // processo filho, lê os dados salvos pelo pai na pipe, processa e imprime
    close(myPipe[1]);
    read(myPipe[0], str, sizeof(str));

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

  return EXIT_SUCCESS;
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
