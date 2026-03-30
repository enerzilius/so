#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/*                                                                             
 * Autor: Eber Felipe Barrotti Louback                                         
 * Descrição: Programa que executa um programa especificado
 * Data de criação: 26/03/2026                                                 
 * Data de modificação: 30/03/2026                                             
*/                                                                             


int main(int argc, char** argv) {
  if(argc < 2) {
      printf("argumentos insuficientes");
      exit(0);
  }

  // separa o nome do arquivo
  char* arguments[argc];
  for(int i = 1; i < argc; ++i) {
      arguments[i-1] = argv[i];
  }

  arguments[argc-1] = (char*)0;
  
  // cria um filho
  pid_t pid;   
  pid = fork();
  if(pid < 0) {
    printf("problema no fork");
    exit(0);
  }

  // se for um filho, usa execv para executar o comando e os argumentos que vem com argv
  if(pid == 0) {
    char src[20] = "/bin/";
    strcat(src, arguments[0]);
    execv(src, arguments);
    exit(0);
  }

  if(pid > 0) {
    int status;
    pid = wait(&status);
    printf("Processo %d foi finalizado com estado %d. \n", pid, status);
  }

  exit(0);
}
