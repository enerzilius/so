#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char *token;
    char *string;
    char *tofree;

    tofree = string = strdup("maçã,banana,,laranja"); // Duplica para permitir modificação

    while ((token = strsep(&string, ",")) != NULL) {
        printf("Token: '%s'\n", token);
    }

    free(tofree); // Libera a memória alocada pelo strdup
    return 0;
}

