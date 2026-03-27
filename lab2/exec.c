#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argv, char** argc) {
    if(argv < 2) {
        printf("argumentos insuficientes");
        exit(0);
    }

    char* arguments[argv-1];
    for(int i = 1; i < argv; ++i) {
        arguments[i-1] = argc[i];
    }

    char buffer[20];
    sprintf(buffer, "/bin/%s", arguments[0]);

    exit(0);
}