#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("argumentos insuficientes");
        exit(0);
    }

    char* arguments[argc];
    for(int i = 1; i < argc; ++i) {
        arguments[i-1] = argv[i];
    }

    arguments[argc-1] = (char*)NULL;

    char src[20];
    sprintf(src, "/bin/%s", arguments[0]);
    printf("%s\n", src);
    
    printf("PID: %d\n", getpid());
    execv(src, arguments);

    exit(0);
}
