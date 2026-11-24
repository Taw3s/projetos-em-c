#include <stdlib.h>   // para malloc e free
#include "vetor.h"    // para conhecer o struct Vetor e os protótipos

// Cria e inicializa um vetor dinâmico com a capacidade informada.
Vetor *vetor_criar(int capacidade) {
    if (capacidade <= 0) {
        return NULL;
    }

    Vetor *v = malloc(sizeof(Vetor));
    if (v == NULL) {
        return NULL;
    }

    v->dados = malloc((size_t)capacidade * sizeof(int));
    if (v->dados == NULL) {
        free(v);
        return NULL;
    }

    v->tamanho = 0;
    v->capacidade = capacidade;
    return v;
}

// Adiciona um valor ao final do vetor; retorna 1 se coube, 0 se estiver cheio ou inválido.
int vetor_adicionar(Vetor *v, int valor) {
    if (v == NULL || v->tamanho == v->capacidade) {
        return 0;
    }

    v->dados[v->tamanho] = valor;
    v->tamanho += 1;
    return 1;
}

// Busca um elemento de forma segura pelo índice; retorna 1 se válido, 0 caso contrário.
int vetor_obter(Vetor *v, int i, int *saida) {
    if (v == NULL || saida == NULL || i < 0 || i >= v->tamanho) {
        return 0;
    }

    *saida = v->dados[i];
    return 1;
}

// Libera toda a memória alocada pelo vetor.
void vetor_destruir(Vetor *v) {
    if (v != NULL) {
        free(v->dados);
        free(v);
    }
}
