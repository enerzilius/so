#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct Livro {
  char titulo[40];
  char autor[30];
  int numPaginas;
};

int main() {
  const char *name = "livro";
  const int SIZE = 4096;

  int shm_fd; // descritor segmento de memoria compartilhada
  void *ptr;  // ponteiro segmento de memoria compartilhada

  // criando um processo filho para não ter que fazer rodar 2 arquivos
  pid_t pid = fork();

  if (pid < 0) {
    perror("Erro no fork ");
    return EXIT_FAILURE;
  }

  // processo pai: producer
  if (pid > 0) {
    /* cria segmento de memoria compartilhada */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* configura o tamanho do segmento */
    ftruncate(shm_fd, SIZE);

    /* mapeia o segmento para o espaco de enderecamento do processo */
    ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
      printf("Map failed\n");
      return EXIT_FAILURE;
    }

    /* escreve para a segmento de memoria compartilhada
     * obs: incrementa-se ponteiro a cada escrita */
    // sprintf(ptr, "%s", message1);
    // ptr += strlen(message1);
    // sprintf(ptr, "%s", message2);
    // ptr += strlen(message2);
  } else {
    /* abre segmento de memoria compartilhada */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
      printf("shared memory failed\n");
      exit(-1);
    }

    /* mapeia segmento no espaco de enderecamento do processo */
    ptr = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
      printf("Map failed\n");
      exit(-1);
    }

    /* le segmento como uma string */
    printf("%s", (char *)ptr);

    /* remove segmento de memoria compartilhada */
    if (shm_unlink(name) == -1) {
      printf("Error removing %s\n", name);
      exit(-1);
    }
  }
  return EXIT_SUCCESS;
}
