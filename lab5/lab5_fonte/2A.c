#include <linux/limits.h>
#include <pwd.h> // pegar o uid e transformar em um nome
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição:Lê atributos de um arquivo, ao receber o sinal sighup, refaz esse
 * processo
 * Data de criação: 29/04/2026
 * Data de modificação: 01/04/2026
 */

void lerConfiguracao();
void sigHandler(int signo);

char *arquivo;
struct stat detalhesArquivo;

int main(int argc, char *argv[]) {
  // precisa que um arquivo seja especificado pelo usuário
  if (argc < 2) {
    printf("Especifique um arquivo!\n");
    exit(EXIT_FAILURE);
  }

  // associa a função tratadora de sinais
  if (signal(SIGHUP, sigHandler) == SIG_ERR)
    printf("\n Não foi possível capturar SIGHUP\n");

  pid_t pid = getpid();
  printf("PID: %u\n", pid);

  arquivo = argv[1];

  lerConfiguracao();

  // loop para esperar receber sinais
  while (1)
    sleep(1);

  return EXIT_SUCCESS;
}

// função tratadora de sinais
void sigHandler(int signo) {
  if (signo == SIGHUP) {
    printf("\n-- SIGHUP recebido.\n");
    lerConfiguracao();
    exit(EXIT_SUCCESS);
  }
}

void lerConfiguracao() {
  if (stat(arquivo, &detalhesArquivo) == -1) {
    perror("Erro ao buscar detalhes do arquivo");
    exit(EXIT_FAILURE);
  }

  char absolutePath[PATH_MAX];
  if (!realpath(arquivo, absolutePath)) {
    perror("Erro ao buscvar caminho absoluto");
    exit(EXIT_FAILURE);
  }

  printf("Caminho absoluto: %s\n", absolutePath);
  printf("Dono: %s\n", getpwuid(detalhesArquivo.st_uid)->pw_name);
  printf("Tamanho: %ld bytes\n", detalhesArquivo.st_size);
  printf("Último acesso: %s", ctime(&detalhesArquivo.st_atime));
  printf("Última modificação: %s", ctime(&detalhesArquivo.st_mtime));
}
