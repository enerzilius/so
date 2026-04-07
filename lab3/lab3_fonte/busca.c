/*                                                                              
 * Autor: Eber Felipe Barrotti Louback                                          
 * Descrição: Busca um número em um vetor de inteiros usando n threads                                                        
 * Data de criação: 07/04/2026                                                  
 * Data de modificação: 07/04/2026                                              
*/                                                                              

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void genRandomVec(int* vec, int n);

int main(int argc, char* argv[]) {
  if(argc < 3) {
    printf("Número insuficiente de argumentos");
    exit(0);
  }

  int tamanhoVetor = atoi(argv[1]);
  int numeroThreads = atoi(argv[2]);

  if(tamanhoVetor < 1 || numeroThreads < 1) {
    printf("O tamanho do vetor e o numero de threads não podem ser menores que 1");
    exit(0);
  }

  // gera um vetor aleatório
  int* vec;
  genRandomVec(&vec, tamanhoVetor);

  // imprime o vetor e o número alvo                 
  for(int i = 0; i < n; ++i) printf("%d ", vec[i]);  
  printf("\n");

  int target = vec[rand()%n];                        
  printf("Elemento a ser encontrado: %d\n", target); 

  // divisão do trabalho
  int workload = tamanhoVetor/numeroThreads;     
  if(workload < 1) workload = 1; 


  // declara, cria e invoca as threads
  //pthread_t t[numeroThreads];

  exit(0);
}

// Recebe um ponteiron de vetor de inteiros, aloca n inteiros 
// e prenche o vetor com números aleatórios                   
void genRandomVec(int* vec, int n) {                         
  *vec = malloc(n * sizeof(int));                             
  srand(time(NULL));                                          
                                                              
  for(int i = 0; i < n; ++i) vec[i] = rand()%n;            
}                                                             


