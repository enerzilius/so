#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição:Lê atributos de um arquivo, ao receber o sinal sighup, refaz esse processo
 * Data de criação: 29/04/2026
 * Data de modificação: 29/04/2026
 */

void lerConfiguracao();
void sigHandler(int signo);

int main(void){
    /* Associa a função tratadora de sinais */
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");

    /* exibe o PID */
    printf("My PID is %d.\n", getpid());

    /* Simulando uma execução de nada */
    while(1)
        sleep(1);
    
    return 0;
}

// função tratadora de sinais
void sigHandler(int signo){
	if (signo == SIGHUP)
		printf("received SIGINT\n");
}
