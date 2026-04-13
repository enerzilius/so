/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição: usa paralelismo de dados e funções para calcular a média aritmetica das linhas
 * e a média geométrica das colunas
 * Data de criação: 09/04/2026        
 * Data de modificação: 12/04/2026    
*/                                    


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "matriz.h"

void *mediaAritmetica(void* params);
void *mediaGeometrica(void* params);
//void criarArquivoTexto(int matriz[][]);

// struct para a thread, marca a linha/coluna que começa,
// a quantidade de linhas/colunas que vai passar e o tamanho dela
struct dataChunk {
  int inicio, workload, tamanho;
  int** matriz;
};

// dados retornados das threads
struct returnData {
  int inicio, quantidade;
  int* resultado;
};

int main(int argc, char* argv[]) {
  if(argc < 2) {
    printf("Diga um número de threads");
    exit(1);
  }

  // salva a quantidade de threads especificada
  int quantidadeThreads = atoi(argv[1]);
  if(quantidadeThreads < 1) {
    printf("quantidade de threads não pode ser menor que 1");
    exit(1);

  }

  // cria uma matriz lendo um arquivo
  int linhas = 6;
  int colunas = 8; 
  int **matriz = read_matrix_from_file("matriz_6por8.in", &linhas, &colunas);
  printf("%d %d\n", linhas, colunas); 
  print_matrix(matriz, linhas, colunas);

  // divisão do trabalho, metade das threads faz a media aritmetica e a outra faz a geométrica
  // define o ínicio (linha/coluna) da thread e quantas ela vai percorrer
  // se só tiver 1 thread não divide
  struct dataChunk dados[quantidadeThreads];
  int metadeThreads = quantidadeThreads/2;
  if(metadeThreads < 1) metadeThreads = 1;
  if(quantidadeThreads > 1) {
    int thread = 0;

    // divisão para média aritmética das linhas
    int inicio = 0;
    int linhasPorThread = linhas/metadeThreads;
    for(int i = 0; i < metadeThreads; i++) {
      dados[thread].inicio = inicio;
      dados[thread].workload = linhasPorThread;
      if(i == metadeThreads-1) dados[thread].workload += linhas%metadeThreads; 
      dados[thread].tamanho = colunas;
      dados[thread].matriz = matriz;
      inicio += linhasPorThread;
      thread++;
    }

    // divisão para a média geométrica das colunas
    inicio = 0;
    int colunasPorThread = colunas/metadeThreads;
    for(int i = 0; i < metadeThreads; i++) {
      dados[thread].inicio = inicio;
      dados[thread].workload = colunasPorThread;
      if(i == metadeThreads-1) dados[thread].workload += colunas%metadeThreads;
      dados[thread].tamanho = linhas;
      dados[thread].matriz = matriz;
      inicio += colunasPorThread;
      thread++;
    }
  } else {
    //se só tiver 1 thread
    dados[0].inicio = 0;
    dados[0].workload = linhas;
    dados[0].tamanho = colunas;
    dados[0].matriz = matriz;
  }

  // cria as threads, ajustando caso só crie uma
  pthread_t threads[quantidadeThreads];
  printf("work: %d\n", dados[0].workload);

  // threads de MA
  for(int i = 0; i < metadeThreads; i++) pthread_create(&threads[i], NULL, mediaAritmetica, &dados[i]);
  int comecoGeometrica = metadeThreads;
  
  if(quantidadeThreads == 1) {
    comecoGeometrica = 0;
    dados[0].workload = colunas;
    dados[0].tamanho = linhas;
  }

  // threads de MG
  for(int i = comecoGeometrica; i < quantidadeThreads; i++) pthread_create(&threads[i], NULL, mediaGeometrica, &dados[i]);
  
  // recupereando os valores vindo das threads
  // cria o vetor com as médias aritméticas
  struct returnData *retVal; 
  int mediaLinhas[linhas];
  for(int i = 0; i < metadeThreads; i++) {
    pthread_join(threads[i], (void**)&retVal);
    printf("aaaa\n");
    for(int j = 0; j < retVal->quantidade; j++) {
      mediaLinhas[retVal->inicio+j] = retVal->resultado[j];
    }
  }

  // cria o vetor com as médias das colunas
  int mediaColunas[colunas];
  for(int i = comecoGeometrica; i < quantidadeThreads; i++) {
    struct returnData *retVal;
    pthread_join(threads[i], (void**)&retVal);
    for(int j = 0; j < retVal->quantidade; j++) {
      mediaColunas[retVal->inicio+j] = retVal->resultado[j];
    }
  }
  free(retVal->resultado);
  free(retVal);

  printf("aritmetica: ");
  for(int i = 0; i < linhas; i++) printf("%d, ", mediaLinhas[i]);
  printf("\n");
  printf("geometrica: ");
  for(int i = 0; i < colunas; i++) printf("%d, ", mediaColunas[i]);
  printf("\n");

  pthread_exit(NULL);

  exit(0);
}

void *mediaAritmetica(void* params) {
  struct dataChunk* dados = params;

  int *results = malloc(sizeof(int) * dados->workload);
  printf("workload: %d\n", dados->workload);
  printf("tamanho: %d\n", dados->tamanho);
  for(int i = 0; i < dados->workload; i++) {
    int sum = 0;
    for(int j = 0; j < dados->tamanho; j++) sum += dados->matriz[dados->inicio+i][j];
    results[i] = sum/dados->tamanho;
  }
  printf("%d\n", results[0]);

  struct returnData *retVal = malloc(sizeof(struct returnData));
  retVal->inicio = dados->inicio;
  retVal->quantidade = dados->workload;
  retVal->resultado = results;
  printf("%d\n", retVal->resultado[0]);

  printf("%d %d %d", retVal->inicio, retVal->quantidade, retVal->resultado[0]);
  
  pthread_exit((void*)retVal);
}

void *mediaGeometrica(void* params) {
  struct dataChunk* dados = params;

  int *results = malloc(sizeof(int) * dados->workload);
  for(int i = 0; i < dados->workload; i++) {
    int produto = 1;
    for(int j = 0; j < dados->tamanho; j++) produto *= dados->matriz[dados->inicio+i][j];
    results[i] = pow(produto, 1.0/dados->tamanho);
  }

  struct returnData *retVal = malloc(sizeof(struct returnData));
  retVal->inicio = dados->inicio;
  retVal->quantidade = dados->workload;
  retVal->resultado = results;

  pthread_exit((void*)retVal);
}

