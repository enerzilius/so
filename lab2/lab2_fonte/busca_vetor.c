#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

/*                                                                             
 * Autor: Eber Felipe Barrotti Louback                                         
 * Descrição: Busca um número em um vetor de tamanho n usando um número
 * determinado de filhos
 * Data de criação: 28/03/2026                                                 
 * Data de modificação: 30/03/2026                                             
*/                                                                             

// Recebe um ponteiron de vetor de inteiros, aloca n inteiros
// e prenche o vetor com números aleatórios
void genRandomVec(int** vec, int n) {
  *vec = malloc(n * sizeof(int));
  srand(time(NULL));

  for(int i = 0; i < n; ++i) (*vec)[i] = rand()%n;
}

int main(int argc, char** argv) {
  int* vec;
  if(argc < 3) { 
    printf("Argumentos faltando!");
    exit(0);
  }
  int n = atoi(argv[1]);
  if(n < 1) {
    printf("O número de elementos não pode ser menor que 1");
    exit(0);
  }
  genRandomVec(&vec, n);

  // imprime o vetor e o número alvo
  for(int i = 0; i < n; ++i) printf("%d ", vec[i]);
  printf("\n");

  int target = vec[rand()%n];
  printf("Elemento a ser encontrado: %d\n", target);
  
  // numero de filhos responsaveis, cada um recebe
  // uma parcela do trabalho
  int children = atoi(argv[2]);
  if(children < 1) {                                                 
    printf("O número de filhos não pode ser menor que 1"); 
    exit(0);                                                  
  }                                                           

  int workload = n/children;
  if(workload < 1) workload = 1;

  for (int i = 0; i < children; ++i) {
    pid_t pid = fork();
    
    if(pid < 0) {
      printf("Erro no fork\n");
      exit(0);
    }
    
    // inicia a busca se o processo for filho
    if(pid == 0) {
      // Se tiver mais filhos que elementos, pula os que não precisam trabalhar
      // se for o último processo, recebe o resto do trabalho que sobrou além
      // da sua cota
      if(i >= n) continue;
      if(i == children-1) workload += n%children;
      for(int j = 0; j < workload; ++j) {
        // acessa a sua porção do vetor
        if(vec[j+i*workload] == target) { 
          printf("Processo %d encontrou %d\n", getpid(), target);
          exit(0);
        }
      }
      exit(1);
    }
  }

  free(vec);

  // espera o resultado e se não receber um status 0 
  // (sucesso), imprime que não encontrou o  número desejado
  for(int i = 0; i < children; ++i) {
    int status;
    wait(&status);
    if(status != 1) exit(0);
  }

  printf("Elemento [%d] não encontrado :(", target);
  exit(0);
}
