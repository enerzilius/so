#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*                                                                              
 * Autor: Eber Felipe Barrotti Louback                                          
 * Descrição: Criar filhos recursivamente, infinitamente                                 
 * Data de criação: 30/03/2026                                                  
 * Data de modificação: 30/03/2026                                              
*/                                                                              


void recursiveForks() {
  pid_t pid = fork();
  if(pid<0) exit(0);
  recursiveForks();
}

int main() {
  recursiveForks();
  exit(0);
}
