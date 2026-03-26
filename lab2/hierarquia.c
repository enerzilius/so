#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if(argc != 2) exit(0);

    int n = atoi(argv[1]);
    if(n < 1) exit(0);

    pid_t root_pid = getpid(); // ← save root before any fork
    int isLeaf = 0;

    for(int i = 0; i < n; ++i) {
      pid_t pid = fork();
      if(pid < 0) exit(0);

      if(i == n-1 && pid == 0) isLeaf = 1;
    }

    if(isLeaf) {
      // Wait a bit so all siblings are spawned before printing
      sleep(1);

      char pid_str[16];
      snprintf(pid_str, sizeof(pid_str), "%d", root_pid); // ← root, not self
      execl("/bin/pstree", "pstree", "-p", pid_str, NULL);
      printf("\n\n");
    }

    wait(NULL);
    exit(0);
}
