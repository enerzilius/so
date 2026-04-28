#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição: Busca um número em um vetor de inteiros usando n threads
 * Data de criação: 28/04/2026
 * Data de modificação: 28/04/2026
 */

int main(int argc, char *argv[]) {
  char str[50];

  int myPipe[2];

  // Criar o pipe
  if (pipe(myPipe)) {
    fprintf(stderr, "Falha ao criar o Pipe.\n");
    return EXIT_FAILURE;
  }

  // criando processo filho
  pid_t pid = fork();
  if (fork < 0) {
    fprintf(stderr, "Falha no fork.\n");
  }

  while (1) {
    // lê as string digitadas pelo usuário
    printf("> ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;
  }
  return EXIT_SUCCESS;
}
