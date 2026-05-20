#include "monitor.h"
#include <pthread.h>

// número de filosofos/garfos
#define N 5

pthread_mutex_t fork_mutex[N];
pthread_cond_t fork_cond[N];
int fork_free[N]; // 0 = sendo usado, 1 = disponivel

void initMonitor() {
  for (int i = 0; i < N; i++) {
    pthread_mutex_init(&fork_mutex[i], NULL);
    pthread_cond_init(&fork_cond[i], NULL);
    fork_free[i] = 1;
  }
}

// pega um garfo
int take(int forkId) {
  pthread_mutex_lock(&fork_mutex[forkId]);
  while (!fork_free[forkId])
    pthread_cond_wait(&fork_cond[forkId], &fork_mutex[forkId]);
  fork_free[forkId] = 0;
  pthread_mutex_unlock(&fork_mutex[forkId]);
  return 1;
}

// solta um garfo e acorda algum filosofo esperando
void put(int forkId) {
  pthread_mutex_lock(&fork_mutex[forkId]);
  fork_free[forkId] = 1;
  pthread_cond_signal(&fork_cond[forkId]);
  pthread_mutex_unlock(&fork_mutex[forkId]);
}

// limpa os mutex
void destroyMonitor() {
  for (int i = 0; i < N; i++) {
    pthread_mutex_destroy(&fork_mutex[i]);
    pthread_cond_destroy(&fork_cond[i]);
  }
}
