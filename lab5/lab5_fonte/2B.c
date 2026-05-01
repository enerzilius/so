
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição:Lê atributos de um arquivo, ao receber o sinal sighup, refaz esse
 * processo Data de criação: 01/04/2026
 * Data de modificação: 01/04/2026
 */

// caminho dos aruqivos de entrada e saída
#define INPUT "input.txt"
#define OUTPUT "output.txt"

int recebeuSinal = 0;

void sigHandler(int signo);
void processarArquivo();

int main(int argc, char *argv[]) {
  // associa a função tratadora de sinais
  if (signal(SIGINT, sigHandler) == SIG_ERR)
    printf("\n Não foi possível capturar SIGINT\n");
  if (signal(SIGTERM, sigHandler) == SIG_ERR)
    printf("\n Não foi possível capturar SIGTERM\n");

  pid_t pid = getpid();
  printf("PID: %u\n", pid);

  processarArquivo();

  return EXIT_SUCCESS;
}

// função tratadora de sinais
void sigHandler(int signo) {
  if (signo == SIGINT || signo == SIGTERM) {
    printf(
        "\n-- Sinal de término recebido: terminando de salvar informações.\n");
    recebeuSinal = 1;
  }
}

// função que lê números em um arquivo
// escreve os números lidos x2 em um arquivo de saída
void processarArquivo() {
  FILE *arquivoInput = fopen(INPUT, "r");
  if (arquivoInput == NULL) {
    perror("Erro ao abrir arquivo de entrada");
    exit(EXIT_FAILURE);
  }

  FILE *arquivoOutput = fopen(OUTPUT, "w");
  if (arquivoOutput == NULL) {
    perror("Erro ao abrir arquivo de saída");
    fclose(arquivoInput);
    exit(EXIT_FAILURE);
  }

  double number;
  int first = 1;

  while (fscanf(arquivoInput, "%lf", &number) == 1) {
    if (!first)
      fprintf(arquivoOutput, "\n");
    fprintf(arquivoOutput, "%g", number * 2);
    // sleep para dar tempo de enviar o sinal
    // depois de receber não faz esse sleep
    if (!recebeuSinal)
      sleep(2);
    first = 0;
  }

  fclose(arquivoInput);
  fclose(arquivoOutput);

  printf("Todos resultados salvos em '%s'\n", OUTPUT);
}
