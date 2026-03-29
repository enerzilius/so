#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void showPsTree(pid_t og_pid) {
  pid_t curr_pid = getpid();
  //if(curr_pid != og_pid) return;
  char pid_str[10];                              
  snprintf(pid_str, 10, "%d", curr_pid);
  execl("/bin/pstree", "pstree", "-p", "-c", "-T", pid_str, (char*)NULL); 
}

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

  pid_t og_pid = getpid();

 for(int i = 0; i < n-1; ++i) {
    pid_t pid = fork();
    if(pid < 0) exit(0);
    if(pid > 0) pid = fork();
    if(pid < 0) exit(0);

    if(pid == 0) {
      continue;
    }

    if(pid > 0) {
      showPsTree(og_pid);
      //if(i == n-1) showPsTree();
      exit(0);
    };
  }

  exit(0);
}
