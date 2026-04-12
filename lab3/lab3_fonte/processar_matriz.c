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

int* *mediaAritmetica(void* params);
int* *mediaGeometrica(void* params);
//void criarArquivoTexto(int matriz[][]);

// struct para a thread, marca a linha/coluna que começa,
// a quantidade de linhas/colunas que vai passar e o tamanho dela
struct dataChunk {
  int inicio, workload, tamanho;
  int** matriz;
};

// dados retornados das threads
struct returnData {
  int posicao, quantidade;
  int* resultado;
}

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
  int linhas = 2;
  int colunas = 3; 
  int matriz[][] = read_matrix_from_file("data_matriz_100_200.in", &linhas, &colunas);
  print_matrix(matrix, r, c);

  // divisão do trabalho, metade das threads faz a media aritmetica e a outra faz a geométrica
  // define o ínicio (linha/coluna) da thread e quantas ela vai percorrer
  // se só tiver 1 thread não divide
  struct dataChunk[numeroThreads];
  int metadeThreads = numeroThreads/2;
  if(metadeThreads < 1) metadeThreads = 1;
  if(quantidadeThreads > 1) {
    int thread = 0;

    int inicio = 0;
    int linhasPorThread = linhas/metadeThreads;
    for(thread < metadeThreads; thread++) {
      dataChunk[thread].inicio = inicio;
      dataChunk[thread].workload = linhasPorThread;
      dataChunk[thread].tamanho = colunas;
      inicio += linhasPorThread;
      thread++;
    }

    inicio = 0;
    int colunasPorThread = colunas/metadeThreads;
    for(int i = 0; i < metadeThreads; i++) {
      dataChunk[thread].inicio = inicio;
      dataChunk[thread].workload = colunasPorThread;
      if(i == metadeThreads-1) dataChunk[thread].workload += colunas%metadeThreads;
      dataChunk[thread].tamanho = linhas;
      inicio += colunasPorThread;
      thread++;
    }
  }

  // cria as threads, ajustando caso só crie uma
  pthread_t threads[numeroThreads];
  for(int i = 0; i < metadeThreads; i++) pthread_create(&threads[i], NULL, mediaAritmetica, &dados[i]);
  if(numeroThreads == 1) metadeThreads = 0;
  for(int i = metadeThreads; i < numeroThreads; i++) pthread_create(&threads[i], NULL, mediaGeometrica, &dados[i]);
  
  int mediaLinhas[linhas];
  for(int i = 0; i < metadeThreads; i++) {
    struct returnValue retVal; 
    pthread_join(threads[i], &retVal);
    for(int j = 0; j < retVal->quantidade; j++) {
      //mediaLinhas[retVal->]
    }
  }

  exit(0);
}

int* *mediaAritmetica(void* params) {
  struct dataChunk* dados = params;
  
  int results[workload];
  for(int i = 0; i < dataChunk->workload; i++) {
    int sum = 0;
    for(int j = 0; j < dataChunk->tamanho; j++) sum +=dataChunk->matriz[inicio+i][j];
    results[i] = sum/tamanho;
  }

  struct returnValue retVal = {dataChunk.inicio, dataChunk.workload, results};
  
  pthread_exit((void*)retVal);
}

int* *mediaGeometrica(void* params) {
  struct dataChunk* dados = params;

  int results[workload];
  for(int i = 0; i < dataChunk->workload; i++) {
    int produto = 0;
    for(int j = 0; j < dataChunk->tamanho; j++) produto +=dataChunk->matriz[inicio+i][j];
    results[i] = pow(produto, 1.0/tamanho);
  }

  struct returnValue retVal = {dataChunk.inicio, dataChunk.workload, results};

  pthread_exit((void*)retVal);
}

