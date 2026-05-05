#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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
 * Data de modificação: 04/04/2026
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

  printf("nfilhos: %d; nelems: %d\n", numeroFilhos, numeroElementos);

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
  void *ptr = mmap(NULL, sizeof(vec) * 3, O_RDWR, MAP_SHARED,
                   shm_fd, 0);
  if (ptr == MAP_FAILED) {
    printf("Map failed\n");
    return EXIT_FAILURE;
  }

  // copia os dados dos vetores para o ponteiro de memória compartilhada
  struct Dados dados = {vec, vec2, vecSoma};
  *(struct Dados *)ptr = dados;

  // dividindo o trabalho
  int workload = numeroElementos / numeroFilhos;
  if (workload < 1)
    workload = 1;

  // pipes
  int pipes[numeroFilhos][2];

  for (int i = 0; i < numeroFilhos; ++i) {
    printf("i: %d\n", i);
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
      shm_fd = shm_open(NAME, O_RDWR, 0666);
      if (shm_fd == -1) {
        perror("falha na abertura da memória compartilhada");
        exit(EXIT_FAILURE);
      }

      // mapeia segmento no espaco de enderecamento do processo
      void *memoriaCompartilhada = mmap(NULL, sizeof(int) * numeroElementos * 3,
                                        O_RDWR, MAP_SHARED, shm_fd, 0);

      if (memoriaCompartilhada == MAP_FAILED) {
        perror("Falha no mapeamento (consumer)\n");
        exit(EXIT_FAILURE);
      }

      struct Dados *dadosLidos = memoriaCompartilhada;

      for (int j = 0; j < trabalho; ++j) {
        dadosLidos->vecSoma[i * trabalho + j] =
            dadosLidos->vec1[i * trabalho + j] +
            dadosLidos->vec2[i * trabalho + j];
        printf("%d: %d\n",i, dadosLidos->vecSoma[i*trabalho+j]);
        fflush(stdout);
      }
      
      exit(EXIT_SUCCESS);
    }
  }

  for(int i = 0; i < numeroFilhos; ++i) wait(NULL);

  struct Dados *dadosRecupeados = ptr;

  for (int i = 0; i < numeroElementos; ++i) {
    printf("%d ", dadosRecupeados->vecSoma[i]);
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
  srand(time(NULL));

  for (int i = 0; i < n; ++i)
    (*vec)[i] = rand() % n;
}
