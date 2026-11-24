#include <stdio.h>

typedef struct {
    int matricula;
    int idade;
    float nota;
} Aluno;

int main(void) {
    Aluno turma[3] = { {101, 18, 7.5}, {102, 20, 9.0}, {103, 19, 6.0} };
    float soma = 0.0; 
    float maior = 0.0;

    // 1. Com um for, imprima cada aluno no formato: Aluno 101: nota 7.5
    for (int i = 0; i < 3; i++) {
        printf("Aluno %d: nota %.1f\n", turma[i].matricula, turma[i].nota);
        soma += turma[i].nota; 
        if (turma[i].nota > maior){
            maior = turma[i].nota;
        }
    }

    // 2. Calcule e imprima a média das notas (soma como float, senão a divisão trunca).
    float media = soma / 3;
    printf("Media da turma: %.2f\n", media);


     // 3. Imprima a matrícula do aluno de maior nota.
    printf("Aluno com maior nota: %.1f\n" , maior)
    

    return 0;
}
