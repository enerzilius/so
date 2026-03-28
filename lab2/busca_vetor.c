#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void genRandomVec(int** vec, int n) {
  *vec = malloc(n * sizeof(int));
  srand(time(NULL));

  for(int i = 0; i < n; ++i) (*vec)[i] = rand()%n;
}

int main(int argc, char* argv[]) {
  int* vec;
  int n = 10;

  genRandomVec(&vec, n);

  for(int i = 0; i < n; ++i) printf("%d ", vec[i]);
  printf("\n");

  int target = vec[rand()%n-1];
  printf("Elemento a ser encontrado: %d\n", target);
  
  int children = 3;
  int workload = n/children;

  for (int i = 0; i < children; ++i) {
    pid_t pid = fork();
    
    if(pid < 0) {
      printf("Erro no fork\n");
      exit(0);
    }

    if(pid == 0) {
      if(i == children-1) workload += n%children;
      for(int j = 0; j < workload; ++j) {
        if(vec[j+i*workload]) { 
          printf("Processo %d encontrou %d", getpid(), target);
          exit(0);
        }
      }
      exit(1);
    }
  }

  free(vec);

  for(int i = 0; i < children; ++i) {
    int status;
    pid_t pid = wait(&status);
    if(status != 1) exit(0);
  }

  printf("Elemento não encontrado :(");
  exit(0);
}
