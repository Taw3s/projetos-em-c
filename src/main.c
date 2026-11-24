#include <stdio.h>
#include "vetor.h"

int main(void) {
    Vetor *notas = vetor_criar(3);
    if (notas == NULL) {
        printf("sem memoria\n");
        return 1;
    }

    int entradas[] = {7, 9, 5, 10};
    for (int i = 0; i < 4; i++) {
        if (vetor_adicionar(notas, entradas[i])) {
            printf("adicionou %d\n", entradas[i]);
        } else {
            printf("cheio! nao coube %d\n", entradas[i]);
        }
    }

    int soma = 0;
    for (int i = 0; i < notas->tamanho; i++) {
        int n;
        if (vetor_obter(notas, i, &n)) {
            soma += n;
        }
    }

    if (notas->tamanho > 0) {
        printf("media: %.2f\n", (double)soma / notas->tamanho);
    }

    int x;
    if (!vetor_obter(notas, 10, &x)) {
        printf("indice 10 invalido\n");
    }

    vetor_destruir(notas);
    return 0;
}
