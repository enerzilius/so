#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void execCommand(char* command) {

}

void mainLoop() {
  printf("Interface Shell!\n\n");
  char command[50];
  while(1) {
    printf(">> ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0;
    
    printf("%s\n", command);

    //pid_t pid = fork();
  }
}

int main(int argc, char** argv) {
  mainLoop();
  exit(0);
}
