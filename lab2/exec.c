#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  if(argc < 2) {
      printf("argumentos insuficientes");
      exit(0);
  }

  char* arguments[argc];
  for(int i = 1; i < argc; ++i) {
      arguments[i-1] = argv[i];
  }

  arguments[argc-1] = (char*)0;

  pid_t pid;   
  pid = fork();
  if(pid < 0) {
    printf("problema no fork");
    exit(0);
  }
  if(pid == 0) {
    char src[20];                          
    sprintf(src, "/bin/%s", arguments[0]); 
    printf("%s\n", src);
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
