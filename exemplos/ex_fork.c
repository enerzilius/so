#include <stdio.h>        // printf()
#include <stdlib.h>       // exit()
#include <unistd.h>       // fork()
#include <sys/types.h>    // pid_t

int main( ){
    pid_t pid;
    int  valor = 0;
 	
    printf ("PID %i - vou criar um filho...\n", getpid());
    
	pid = fork( ); /* cria um processo e devolve pid do filho 
                      para o pai e 0 para o filho */
                      
    printf("PID %i - executando ....\n", getpid());                  

    if (pid) {
        /* este trecho é executado pelo pai */
		printf("Eu Sou o Processo Pai - Filho pid(var) %d \n", pid);
        valor = 5;
        printf("Valor: %d \n", valor);
    }
    else {
        /* este trecho é executado pelo filho */
   		printf("Eu Sou o Processo Filho - Filho pid(var) %d, em pai %d \n", pid, getppid());
        valor = 10;
        printf("Valor: %d \n", valor);
    }
    
    exit(0);        
}
