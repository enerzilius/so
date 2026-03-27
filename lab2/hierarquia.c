#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("argumentos insuficientes");
    exit(0);
  }
  int n = atoi(argv[1]);
  if(n < 1) {
    printf("n não pode ser menor que 1");
    exit(0);
  }

  // pid_t root_pid = getpid();

  for(int i = 0; i < n; ++i) {
    pid_t pid = fork();
    if(pid < 0) exit(0);
  }

  // char pid_str[16];
  // system("pstree -c -T", pid_str, NULL);
  // printf("\n\n");

  wait(NULL);
  exit(0);
}
