#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>

#define N_SELVAGENS 3
#define PORCOES 6

sem_t servindo;
sem_t caldeirao_vazio;
sem_t caldeirao_tem_coisa;

void *cozinheiro();
void *selvagem();
void servir();
void comer();
void encher_caldeirao();

int main(){
    pthread_t threads[N_SELVAGENS+1];
    pthread_attr_t attr;

    sem_init(&servindo, 1, 1);
    sem_init(&caldeirao_vazio, 1, 1);
    sem_init(&caldeirao_tem_coisa, 1, 0);

    /* criar as threads */
    pthread_create (&threads[0], NULL, (void *) &cozinheiro, NULL);
    for (int i=1; i <= N_SELVAGENS; i++) {
        pthread_create (&threads[i], NULL, (void *) &selvagem, NULL);
    }

    for (int i=0; i <= N_SELVAGENS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&servindo); /* destroy semaphore */
    sem_destroy(&caldeirao_vazio); /* destroy semaphore */
    sem_destroy(&caldeirao_tem_coisa); /* destroy semaphore */

    exit(EXIT_SUCCESS);
}

void *cozinheiro() {
    while(1) {
        sem_wait(&caldeirao_vazio);
        encher_caldeirao();   
    }
}

void *selvagem() {
    while(1) {
        servir();
        comer();
    }
}

void servir() {
    sem_wait(&servindo);
    sem_wait(&caldeirao_tem_coisa);
    printf("Selvagem se servindo!\n");
    sleep(1);
    sem_post(&servindo);
    sem_post(&caldeirao_vazio);
}

void comer() {
    printf("comeno dog\n");
    sleep(1);
}

void encher_caldeirao() {
    printf("enchendo caldeirao...\n");
    for(int i = 0; i < PORCOES; ++i) {
        sem_post(&caldeirao_tem_coisa);
    }
}