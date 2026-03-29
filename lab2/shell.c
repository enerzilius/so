#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void execCommand(char* command) {
  
}

int countWords(char* str) {
  int c = 1;
  for(int i = 0; i<strlen(str); i++) if(str[i] == ' ') c++;
  return c;
}

void mainLoop() {
  printf("Interface Shell!\n\n");
  char command[50];
  while(1) {
    printf(">> ");
    fgets(command, sizeof(command), stdin);
    printf("\n");
    command[strcspn(command, "\n")] = 0;
    
    int argc = countWords(command);
    char* arguments[argc];
    char* temp = command;
    for (int i = 0; i < argc && (arguments[i] = strsep(&temp, " ")) != NULL; ++i); 
    free(temp);
    char* lastArg = arguments[argc-1];
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

    if(lastArg[0] != '&') {
      int status;    
      wait(&status);
    }
  }
}

int main(int argc, char** argv) {
  mainLoop();
  exit(0);
}
