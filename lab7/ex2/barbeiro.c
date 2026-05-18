/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição: Algoritmo para resolver o problema do barbeiro dorminhoco:
 * Barbeiro dorme se não estiver trabalhando
 * Se algum cliente chegar e o barbeiro estiver dormindo: barbeiro é acordado
 * Se algum cliente chegar e ele estiver trabalhando: entra na fila
 * Data de criação: 18/05/2026
 * Data de modificação: 18/05/2026
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N_CLIENTES 2
#define CADEIRAS 1

sem_t mutex;
sem_t esperando;
sem_t cadeiraBarbeiro;
int cadeirasUsadas = 0;

void *barbeiro();
void *cliente();

int main() {
  pthread_t threads[N_CLIENTES + 1];

  sem_init(&mutex, 1, 1);
  sem_init(&esperando, 1, 0);
  sem_init(&cadeiraBarbeiro, 1, 1);

  /* criar as threads */
  pthread_create(&threads[0], NULL, (void *)&barbeiro, NULL);
  for (int i = 1; i <= N_CLIENTES; i++) {
    sleep(1);
    pthread_create(&threads[i], NULL, (void *)&cliente, NULL);
  }

  for (int i = 0; i <= N_CLIENTES; i++) {
    pthread_join(threads[i], NULL);
  }

  sem_destroy(&esperando);       /* destroy semaphore */
  sem_destroy(&esperando);       /* destroy semaphore */
  sem_destroy(&cadeiraBarbeiro); /* destroy semaphore */

  exit(EXIT_SUCCESS);
}

void *barbeiro() {
  while (1) {
    printf("Barbeiro: Dormindo... zzzzzz...\n");
    sem_wait(&esperando);
    printf("Barbeiro: Cortando cabelo\n");
    --cadeirasUsadas;
    sleep(2);
    sem_post(&cadeiraBarbeiro);
    printf("Cabelo cortado!\n");
  }
}

void *cliente() {
  sem_wait(&mutex);
  if (cadeirasUsadas >= CADEIRAS) {
    printf("Cliente saindo pois está cheio\n");
    sem_post(&mutex);
    return (NULL);
  }

  sem_post(&esperando);
  printf("Cliente esperando...\n");
  ++cadeirasUsadas;
  sem_post(&mutex);
  sem_wait(&cadeiraBarbeiro);
  return (NULL);
}
