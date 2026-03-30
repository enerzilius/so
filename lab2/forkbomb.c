#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void recursiveForks() {
  pid_t pid = fork();
  if(pid<0) exit(0);
  recursiveForks();
}

int main() {
  recursiveForks();
  exit(0);
}
