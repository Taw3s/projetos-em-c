#ifndef VETOR_H
#define VETOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int *dados;       // array reservado com malloc
    int tamanho;      // quantos elementos estão em uso
    int capacidade;   // quantos cabem
} Vetor;

Vetor *vetor_criar(int capacidade);              // NULL se falhar
int    vetor_adicionar(Vetor *v, int valor);     // 1 se coube, 0 se cheio
int    vetor_obter(Vetor *v, int i, int *saida); // 1 se i é válido, 0 se não; valor em *saida
void   vetor_destruir(Vetor *v);                 // libera tudo

#ifdef __cplusplus
}
#endif

#endif