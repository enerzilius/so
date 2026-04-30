#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Autor: Eber Felipe Barrotti Louback
 * Descrição: rograma que lê uma expressão matemática simples (+, -, *, /) e passe para outro
programa que realiza o cálculo e devolve a resposta - usando pipe
 * Data de criação: 29/04/2026
 * Data de modificação: 29/04/2026
 */

 // usa o operador passado para realizar o cálculo dos números escritos
 int calcular(int num1, int num2, char op);

 int main(int argc, char* argv[]) {
    char str[51];

  int myPipe[2];

  // Criar o pipe
  if (pipe(myPipe)) {
    fprintf(stderr, "Falha ao criar o Pipe.\n");
    return EXIT_FAILURE;
  }

  // criando processo filho
  pid_t pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Falha no fork.\n");
    return EXIT_FAILURE;
  }

  // processo pai, lê a operação escrita pelo usuário
  if (pid != 0) {
    close(myPipe[0]);
    printf("Digite um cálculo simples (+, -, *, /) escrito como a + b : ");
    scanf("%50[^\n]", str);
    write(myPipe[1], str, sizeof(str));

    wait(NULL);
    return EXIT_SUCCESS;
  } else {
    // processo filho, lê os dados salvos pelo pai na pipe, processa e imprime
    close(myPipe[1]);
    read(myPipe[0], str, sizeof(str));

    
    char* arguments[4];
    char* temp = str;

    // processa o que foi passado pela pipe:
    // divide em um vetor e traduz para números e oparador em char

    for (int i = 0; i < 3 && (arguments[i] = strsep(&temp, " ")) != NULL; ++i); 
    free(temp);
    arguments[3] = (char*)0;

    int num1 = atoi(arguments[0]);
    char operador = arguments[1][0];
    int num2 = atoi(arguments[2]);

    // verifica se a operação é válida
    if(operador != '+' && operador != '-' && operador != '*' && operador != '/') {
        printf("operação não permitida.");
        return EXIT_FAILURE;
    }

    int resultado = calcular(num1, num2, operador);

    printf("%d %c %d = %d\n", num1, operador, num2, resultado);

    fflush(stdout);
    return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
 }

int calcular(int num1, int num2, char op) {
    switch (op)
    {
        case '+':
            return num1 + num2;
        case '-':
            return num1-num2;
        case '*':
            return num1*num2;
        case '/':
            return num1/num2;
        default:
            return -1;
    }
}