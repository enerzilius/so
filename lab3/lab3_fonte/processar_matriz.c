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

// vetores que armazenam os resultados das médias
int* resultadoLinhas;
int* resultadoColunas;

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

  // define o tamanho dos vetores de retorno do resultado
  resultadoLinhas = malloc(sizeof(int) * linhas);
  resultadoColunas = malloc(sizeof(int) * colunas);

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
  // threads de MA
  for(int i = 0; i < metadeThreads; i++) pthread_create(&threads[i], NULL, mediaAritmetica, &dados[i]);
  int comecoGeometrica = metadeThreads;
  
  // se só tiver uma thread, inverte o tamanho e workload
  if(quantidadeThreads == 1) {
    comecoGeometrica = 0;
    for(int i = 0; i < metadeThreads; i++) {
      pthread_join(threads[i], NULL);
    }
    dados[0].workload = colunas;
    dados[0].tamanho = linhas;
  }

  // threads de MG
  for(int i = comecoGeometrica; i < quantidadeThreads; i++) pthread_create(&threads[i], NULL, mediaGeometrica, &dados[i]);
  
  for(int i = 0; i < quantidadeThreads; i++) pthread_join(threads[i], NULL);
  
  free(resultadoColunas);
  free(resultadoLinhas);

  exit(0);
}

void *mediaAritmetica(void* params) {
  struct dataChunk* dados = params;

  
  for(int i = 0; i < dados->workload; i++) {
    int sum = 0;
    for(int j = 0; j < dados->tamanho; j++) sum += dados->matriz[dados->inicio+i][j];
    resultadoLinhas[dados->inicio+i] = sum/dados->tamanho;
  }

  pthread_exit(NULL);
}

void *mediaGeometrica(void* params) {
  struct dataChunk* dados = params;

  for(int i = 0; i < dados->workload; i++) {
    int produto = 1;
    for(int j = 0; j < dados->tamanho; j++) produto *= dados->matriz[j][dados->inicio+i];
    resultadoColunas[dados->inicio+i] = pow(produto, 1.0/dados->tamanho);
  }

  pthread_exit(NULL);
}

