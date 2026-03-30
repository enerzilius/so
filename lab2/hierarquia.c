#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição: Código cria hierarquia de processos. Tamanho especificado 
 * ao rodar o programa, cada nível depois do primeiro cria 2 processos filhos 
 * Data de criação: 26/03/2026
 * Data de modificação: 30/03/2026
*/

// Executa o comando pstree do pid do processoo mostrando os pid, sem compactar e escondendo threads
void showPsTree() {
  pid_t curr_pid = getpid();
  char pid_str[10];                              
  snprintf(pid_str, 10, "%d", curr_pid);
  execl("/bin/pstree", "pstree", "-p", "-c", "-T", pid_str, (char*)NULL); 
}


int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("argumentos insuficientes");
    exit(0);
  }
  int layers = atoi(argv[1]);
  if(layers < 1) {
    printf("o número de camadas não pode ser menor que 1");
    exit(0);
  }

  //pid_t og_pid = getpid();

  if(layers==1) showPsTree(); // como 1 não entra no for, já faz o pstree aqui
  
  //cria iterativamente 2 filhos pra cada camada
  for(int i = 0; i < layers-1; ++i) {
    pid_t pid = fork();
    if(pid < 0) exit(0);
    if(pid > 0) pid = fork();
    if(pid < 0) exit(0);

    if(pid == 0) {
      continue;
    }

    if(pid > 0) break;
  }

  showPsTree();
  int status;
  wait(&status);

  exit(0);
}
