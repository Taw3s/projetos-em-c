#include <stdio.h>

typedef struct {
    int matricula;
    int idade;
    float nota;
} Aluno;

int main(void) {
    
    Aluno a1 = {101, 18, 7.5};   // ordem dos campos: matricula, idade, nota
    Aluno a2 = {102, 20, 9.0};

    printf("Aluno %d: idade %d, nota %.1f\n", a1.matricula, a1.idade, a1.nota);
    printf("Aluno %d: idade %d, nota %.1f\n", a2.matricula, a2.idade, a2.nota);

    if (a1.nota > a2.nota) {
        printf("Maior nota : aluno %d\n" , a1.matricula);
    } else {
        printf("Maior nota : aluno %d\n", a2.matricula);
}
    Aluno a3 = a1;
    a3.nota = 3.0;

    //    Imprima a1.nota e a3.nota.
    printf("Aluno a1: %.1f\n" , a1.nota);
    printf("Aluno a3: %.1f\n" , a3.nota);

    return 0;
}