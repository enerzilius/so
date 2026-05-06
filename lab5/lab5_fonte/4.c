#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição:Lê atributos de um arquivo, ao receber o sinal sighup, refaz esse
 * processo Data de criação: 04/04/2026
 * Data de modificação: 06/04/2026
 */

#define NAME "vetor"

void gerarRandomVec(int **vec, int n);

// struct que vai armazenar os vetores compartilhados
struct Dados {
  int *vec1;
  int *vec2;
  int *vecSoma;
};

int main(int argc, char *argv[]) {
  srand(time(NULL));
  if (argc < 3) {
    printf("Determine o número de elementos e o número de filhos\n");
    return EXIT_FAILURE;
  }

  // lendo e validando os dados vindos do usuário
  int *vec;
  int *vec2;
  int *vecSoma;

  int numeroElementos = atoi(argv[1]);
  int numeroFilhos = atoi(argv[2]);

  if (numeroElementos < 1) {
    printf("O número de elementos não pode ser menor que 1\n");
    return EXIT_FAILURE;
  }
  if (numeroFilhos < 1) {
    printf("O número de filhos não pode ser menor que 1\n");
    return EXIT_FAILURE;
  }

  // gerando vetor
  gerarRandomVec(&vec, numeroElementos);
  gerarRandomVec(&vec2, numeroElementos);
  vecSoma = malloc(sizeof(int) * numeroElementos);

  // colocando o vetor na memória compartilhada
  // cria segmento de memoria compartilhada
  int shm_fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);

  // configura o tamanho do segmento
  ftruncate(shm_fd, sizeof(int) * numeroElementos * 3);

  // mapeia o ponteiro com o tamanho do vetor na memória compartilhada
  void *ptr = mmap(NULL, sizeof(int) * numeroElementos * 3,
                   PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    printf("Map failed\n");
    return EXIT_FAILURE;
  }

  // colocando os vetores na memória compartilhada
  int *shmVec1 = (int *)ptr;
  int *shmVec2 = shmVec1 + numeroElementos;
  int *shmVecSoma = shmVec2 + numeroElementos;
  memcpy(shmVec1, vec, sizeof(int) * numeroElementos);
  memcpy(shmVec2, vec2, sizeof(int) * numeroElementos);
  memcpy(shmVecSoma, vecSoma, sizeof(int) * numeroElementos);

  // dividindo o trabalho
  int workload = numeroElementos / numeroFilhos;
  if (workload < 1)
    workload = 1;

  // pipes
  int pipes[numeroFilhos][2];

  for (int i = 0; i < numeroFilhos; ++i) {
    if (i >= numeroElementos)
      continue;
    if (i == numeroFilhos - 1)
      workload += numeroElementos % numeroFilhos;

    // criando a pipe do filho
    if (pipe(pipes[i])) {
      fprintf(stderr, "Falha ao criar o Pipe.\n");
      return EXIT_FAILURE;
    }

    // escrevendo trabalho do filho
    char stringNumero[12];
    sprintf(stringNumero, "%d", workload);

    pid_t pid = fork();

    if (pid < 0) {
      perror("Erro no fork");
      exit(EXIT_FAILURE);
    }

    // pai escreve o número de elementos que o filho vai ler
    if (pid > 0) {
      close(pipes[i][0]);
      write(pipes[i][1], stringNumero, sizeof(stringNumero));
    }

    if (pid == 0) {
      close(pipes[i][1]);

      // lendo o trabalho
      char lido[12];
      read(pipes[i][0], lido, sizeof(char) * 12);
      int trabalho = atoi(lido);

      // abre segmento de memoria compartilhada cmo leitura
      int shm_fd_child = shm_open(NAME, O_RDWR, 0666);
      if (shm_fd_child == -1) {
        perror("falha na abertura da memória compartilhada");
        exit(EXIT_FAILURE);
      }

      // mapeia segmento no espaco de enderecamento do processo
      void *dadosLidos =
          mmap(NULL, sizeof(int) * numeroElementos * 3, PROT_READ | PROT_WRITE,
               MAP_SHARED, shm_fd_child, 0);

      if (dadosLidos == MAP_FAILED) {
        perror("Falha no mapeamento (consumer)\n");
        exit(EXIT_FAILURE);
      }

      // dividindo os vetores lidos
      int *vetorLido1 = (int *)dadosLidos;
      int *vetorLido2 = vetorLido1 + numeroElementos;
      int *vetorSoma = vetorLido2 + numeroElementos;

      for (int j = 0; j < trabalho; ++j) {
        int index = i * trabalho + j;
        vetorSoma[index] = vetorLido1[index] + vetorLido2[index];
      }

      exit(EXIT_SUCCESS);
    }
  }

  // espera todos os filhos terminarem
  for (int i = 0; i < numeroFilhos; ++i)
    wait(NULL);

  // lê os resultados
  for (int i = 0; i < numeroElementos; ++i) {
    printf("%d ", shmVecSoma[i]); // lê da memória compartilhada
  }
  printf("\n");

  // remove segmento de memoria compartilhada
  if (shm_unlink(NAME) == -1) {
    perror("Erro no unlink ");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}

// Recebe um ponteiron de vetor de inteiros, aloca n inteiros
// e prenche o vetor com números aleatórios
void gerarRandomVec(int **vec, int n) {
  *vec = malloc(n * sizeof(int));

  for (int i = 0; i < n; ++i)
    (*vec)[i] = rand() % n;
}
