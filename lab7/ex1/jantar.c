/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição: Algoritmo para resolver o problema do jantar dos filosofos:
 * filosofos: pensam, ficam com fome e tentam pegar dois garfos, quando
 * conseguem, comem e devolvem os garfos.
 * Na mesa tem 5 pratos e 5 garfos
 * Fazer com que consigam comer sem causar deadlock
 * Data de criação: 20/05/2026
 * Data de modificação: 20/05/2026
 */

#include "monitor.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5

// lógica do filosofo
void *philosopher(void *arg);

int main(void) {
  // threads (fiósofos)
  pthread_t threads[N];
  int ids[N];

  // inicializando o monitor
  initMonitor();

  // criando as threads
  for (int i = 0; i < N; i++) {
    ids[i] = i;
    pthread_create(&threads[i], NULL, philosopher, &ids[i]);
  }

  // esperando o termino das threads
  for (int i = 0; i < N; i++)
    pthread_join(threads[i], NULL);

  return EXIT_SUCCESS;
}

void *philosopher(void *arg) {
  int id = *(int *)arg;

  // Hierarquia de recursos: sempre pega o garfo de menor ID
  // Ex: filosofo 4 pega o 0 antes do 4 quebrando a simetria.
  int left = id;
  int right = (id + 1) % N;
  int first = (left < right) ? left : right;
  int second = (left < right) ? right : left;

  while (1) {
    printf("Filósofo %d está pensando... (logo, existe)\n", id);
    sleep(1);

    // com fome: pega os garfos
    take(first);
    printf("Filósofo %d pegou o garfo %d\n", id, first);
    take(second);
    printf("Filósofo %d pegou o garfo %d\n", id, second);

    printf("Filósofo %d está comendo!  (garfos %d & %d)\n", id, first, second);
    sleep(2);

    // devolve os garfos
    printf("Filósofo %d está devolvendo os garfos %d e %d\n", id, first,
           second);
    put(first);
    put(second);
  }

  return (NULL);
}
