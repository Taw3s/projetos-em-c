#include <stdio.h>    // necessário para o printf
#include <stdlib.h>   // para malloc e free

typedef struct {
    int *dados;       // array reservado com malloc
    int tamanho;      // quantos elementos estão em uso
    int capacidade;   // quantos cabem
} Vetor;

// Cria e inicializa o vetor
Vetor* vetor_criar(int capacidade) {

    Vetor *v = (Vetor*) malloc(sizeof(Vetor)); //reserva a caixa do struct 'v' e guarda o endereco dela 

    if (v == NULL) return NULL; 

    v->dados = (int*) malloc(capacidade * sizeof(int)); // reserva o array e guarda o endereco dentro do struct
    if (v->dados == NULL) {
        free(v);
        return NULL;
    }

    v->tamanho = 0;
    v->capacidade = capacidade;
    return v;

}

int vetor_adicionar(Vetor *v, int valor) {
    if (v->tamanho == v->capacidade) {        // verifica se atingiu o limite
        return 0;
    }

    v->dados[v->tamanho] = valor; // grava na próxima posição livre
    v->tamanho += 1;              // incrementa o tamanho corretamente
    return 1;
}

// Busca um elemento de forma segura pelo índice
int vetor_obter(Vetor *v, int indice, int *saida) {
    if (indice < 0 || indice >= v->tamanho) {
        return 0; 
    }
    *saida = v->dados[indice];
    return 1;
}

// Libera a memória alocada
void vetor_destruir(Vetor *v) {
    if (v != NULL) {
        free(v->dados);
        free(v);
    }
}

int main(void) {
    Vetor *notas = vetor_criar(3);          // corrigido de vetor_d para vetor_criar
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
