#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

/*                                                                             
 * Autor: Eber Felipe Barrotti Louback                                         
 * Descrição: Programa de interface shell que executa comandos           
 * Data de criação: 29/03/2026                                                 
 * Data de modificação: 30/03/2026                                             
*/                                                                             

// str: string de input do usuário
// conta os espaços em branco para determinar o número de palavras
int countWords(char* str) {
  int c = 1;
  for(int i = 0; i<strlen(str); i++) if(str[i] == ' ') c++;
  return c;
}

// Loop de funcionamento principal
// Responsável por ler o input, processá-lo e executar o comando desejado
void mainLoop() {
  printf("Interface Shell!\n\n");
  char command[50];
  while(1) {
    // lê o input do usuário
    printf(">> ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0;
    
    // cria um vetor de string com os argumentos
    int argc = countWords(command);
    char* arguments[argc];
    char* temp = command;
    for (int i = 0; i < argc && (arguments[i] = strsep(&temp, " ")) != NULL; ++i); 
    free(temp);
    char* lastArg = arguments[argc-1];
    // se terminar com &, remove ele do vetor para não dar problema
    if(lastArg[0] == '&') arguments[argc-1] = (char*)0;
    arguments[argc] = (char*)0;
    
    char src[20] = "/bin/";
    strcat(src, arguments[0]);

    pid_t pid = fork();
    if(pid<0) {
      printf("Erro no fork\n");
      exit(0);
    }
  
    if(pid == 0) {
      execv(src, arguments);
      exit(0);
    }
    // se receber o &, conitnua o funcionamento do programa sem esperar
    if(lastArg[0] == '&') {
      continue;
    }

    int status;   
    wait(&status);
  }
}

int main(int argc, char** argv) {
  mainLoop();
  exit(0);
}
