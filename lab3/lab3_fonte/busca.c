/*                                                                              
 * Autor: Eber Felipe Barrotti Louback                                          
 * Descrição: Busca um número em um vetor de inteiros usando n threads                                                        
 * Data de criação: 07/04/2026                                                  
 * Data de modificação: 07/04/2026                                              
*/                                                                              

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void genRandomVec(int** vec, int n);
void* busca(void* param);

struct data_chunk {                           
    int inicioParte, finalParte;
};                             

int alvo;
int *vec;

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
  genRandomVec(&vec, tamanhoVetor);

  // imprime o vetor e o número alvo                 
  for(int i = 0; i < tamanhoVetor; ++i) printf("%d ", vec[i]);  
  printf("\n");

  alvo = vec[rand()%tamanhoVetor];
  printf("Elemento a ser encontrado: %d\n", alvo); 

  // divisão do trabalho
  struct data_chunk dados[numeroThreads];
  int workload = tamanhoVetor/numeroThreads;     
  if(workload < 1) workload = 1; 

  int inicioParte = 0;
  int finalParte = workload;

  for(int i = 0; i < numeroThreads; ++i) {
    dados[i].inicioParte = inicioParte;
    dados[i].finalParte = finalParte;

    if(i == numeroThreads-1) {
      finalParte += tamanhoVetor%numeroThreads;
    }

    inicioParte = finalParte+1;
    finalParte += workload;
  }


  // declara, cria e invoca as threads
  pthread_t threads[numeroThreads];
  for(int i = 0; i < numeroThreads; i++) pthread_create(&threads[i], NULL, busca, &dados[i]);
  
  for(int i = 0; i < numeroThreads; i++) pthread_join(threads[i], NULL);
  exit(0);
}

// Recebe um ponteiron de vetor de inteiros, aloca n inteiros 
// e prenche o vetor com números aleatórios                   
void genRandomVec(int** vec, int n) { 
  printf("Gerando vetor...\n");
  *vec = malloc(n * sizeof(int));                             
  srand(time(NULL));                                          
                                                              
  for(int i = 0; i < n; ++i) (*vec)[i] = rand()%n;            
}                                                             


// usa os dados vindos do parametro para encontrar o número alvo no vetor
void* busca(void* param) {
  struct data_chunk* dados = param;
  
  for(int i = dados->inicioParte; i <= dados->finalParte;i++){
    if(vec[i] == alvo) {
      printf("%lu encontrou o número %d na posicição %d.\n", pthread_self(), vec[i], i);
    }
  }
  return(NULL);
}
