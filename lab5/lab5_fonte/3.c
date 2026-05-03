#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct Livro {
  char titulo[40];
  char autor[30];
  int numPaginas;
};

int main() {
  const char *name = "livro";
  int shm_fd; // descritor segmento de memoria compartilhada

  // criando um processo filho para não ter que rodar em 2 arquivos
  pid_t pid = fork();

  if (pid < 0) {
    perror("Erro no fork ");
    return EXIT_FAILURE;
  }

  // processo pai: producer
  if (pid > 0) {
    printf("Processo pai (%d): producer\n", getpid());

    // cria segmento de memoria compartilhada
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    // configura o tamanho do segmento
    ftruncate(shm_fd, sizeof(struct Livro));

    struct Livro livro = {"titulo do livro", "autor do livro", 67};
    // mapeia o struct Livro na memória compartilhada
    void *ptr = mmap(NULL, sizeof(struct Livro), PROT_READ | PROT_WRITE,
                     MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
      printf("Map failed\n");
      return EXIT_FAILURE;
    }

    // copia os dados do livro para o ponteiro de memória compartilhada
    *(struct Livro *)ptr = livro;

    // espera o processo filho acabar antes de finalizar
    wait(NULL);
    return EXIT_SUCCESS;
  } else { // processo filho, consumer
    // espera o dado ser salvo antes de acessar a memória
    sleep(2);

    // abre segmento de memoria compartilhada cmo leitura
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
      printf("shared memory failed\n");
      exit(EXIT_FAILURE);
    }

    // mapeia segmento no espaco de enderecamento do processo
    void *ptr =
        mmap(NULL, sizeof(struct Livro), PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
      printf("Falha no mapeamento (consumer)\n");
      exit(EXIT_FAILURE);
    }

    printf("Processo filho (%d) consumiu: \n", getpid());

    // atribui os dados lidos na memória para um ponteiro de tipo Livro
    struct Livro *livro = ptr;
    printf("Título: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Número de páginas: %d", livro->numPaginas);

    // remove segmento de memoria compartilhada
    if (shm_unlink(name) == -1) {
      printf("Erro removendo %s\n", name);
      exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
  }
}
