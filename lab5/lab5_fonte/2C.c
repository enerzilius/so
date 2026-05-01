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

// volatile: sempre fica na memória
volatile sig_atomic_t keep_going = 1;

// segundos até terminar
int segundos = 10;

// trata o sinal
void sigHandler(int signo);
// faz a contagem regressiva
void countdown();

int main(void) {
  // tratador para sinais SIGINT
  if (signal(SIGINT, sigHandler) == SIG_ERR)
    printf("\n Não foi possível capturar SIGHUP\n");
  if (signal(SIGALRM, sigHandler) == SIG_ERR)
    printf("\n Não foi possível capturar SIGALRM\n");

  pid_t pid = getpid();
  printf("PID: %d\n", pid);

  // fica esperando
  while (1)
    sleep(1);

  puts("Terminou.");

  return EXIT_SUCCESS;
}

void sigHandler(int signo) {
  if (signo == SIGINT) {
    puts("\n--SIGINT recebido, finalizando em 10 segundos\n");
    alarm(10);
    countdown();
  }
  if (signo == SIGALRM)
    exit(EXIT_SUCCESS);
}

void countdown() {
  while (segundos > 0) {
    printf("%d\n", segundos);
    segundos--;
    sleep(1);
  }
}
