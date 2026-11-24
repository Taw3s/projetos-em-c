#include <stdio.h>

typedef struct {
    int matricula;
    int idade;
    float nota;
} Aluno;


void aumentar_por_valor(Aluno a) {
    a.nota = a.nota + 1.0; //cria uma copia de x , sendo a
    printf("Valor aumentado: %.1f\n", a.nota);
}

// Recebe o ENDEREÇO do aluno. Some 1.0 na nota do aluno original.
void aumentar_por_ponteiro(Aluno *a) {
    a->nota += 1.0; //referencia o enderecamento de x , sendo x o endereco e o a aquele que referencia , uma caixa nova
}

int main(void) {
    Aluno x = {101, 18, 7.0};

    aumentar_por_valor(x);
    printf("depois por valor: %.1f\n", x.nota);

    aumentar_por_ponteiro(&x);
    printf("depois por ponteiro: %.1f\n", x.nota);

    return 0;
}
