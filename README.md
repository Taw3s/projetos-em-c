# Projeto em C - Vetores

Implementação modular de um **vetor dinâmico de inteiros** em C, com alocação dinâmica de memória (`malloc` / `free`) e verificação de limites.

## Estrutura do Projeto

```text
Projeto em C - Vetores/
├── include/
│   └── vetor.h          # Interface pública (struct Vetor e protótipos, com extern "C")
├── src/
│   ├── main.c           # Programa principal em C (registro de notas e média)
│   └── vetor.c          # Implementação das funções do vetor dinâmico
├── extras/
│   ├── bench.cpp        # Benchmark em C++ (<chrono>): Vetor (C) vs std::vector
│   └── leitor.cpp       # Leitor de notas em C++ (<fstream>) usando Vetor (C)
├── data/
│   └── notas.txt        # Arquivo de exemplo para o leitor.cpp
├── build/
│   ├── obj/             # Objetos compilados (.o)
│   └── bin/             # Executáveis gerados (.exe)
├── testes/              # Exercícios anteriores de estudo
├── registro de notas/   # Código bruto original de referência
├── Makefile             # Automação de build (gcc / g++)
└── README.md            # Documentação e explicação linha a linha
```

---

## Explicação Detalhada de Cada Bloco e Linha em C

### 1. Arquivo `vetor.h` (Interface / Cabeçalho)

#### Bloco 1.1: Include Guards (`#ifndef` / `#define` / `#endif`)
```c
#ifndef VETOR_H
#define VETOR_H
// ... conteúdo do cabeçalho ...
#endif
```
- `#ifndef VETOR_H`: verifica se a constante `VETOR_H` ainda **não** foi definida ("if not defined").
- `#define VETOR_H`: define `VETOR_H` na primeira vez que o arquivo é incluído, evitando que o conteúdo seja processado duas vezes caso vários arquivos incluam `"vetor.h"`.
- `#endif`: fecha o bloco condicional iniciado por `#ifndef`.

#### Bloco 1.2: Definição da `struct Vetor`
```c
typedef struct {
    int *dados;       // array reservado com malloc
    int tamanho;      // quantos elementos estão em uso
    int capacidade;   // quantos cabem
} Vetor;
```
- `typedef struct {`: inicia a definição de uma estrutura de dados agrupando variáveis relacionadas e cria um apelido (`typedef`) para ela.
- `int *dados;`: ponteiro para `int` que guardará o endereço do bloco de memória alocado dinamicamente para armazenar os números.
- `int tamanho;`: contador de quantos elementos já foram inseridos e estão em uso no momento.
- `int capacidade;`: limite máximo de elementos que cabem no espaço reservado em `dados`.
- `} Vetor;`: fecha a estrutura e dá a ela o nome de tipo `Vetor` (assim não é preciso escrever `struct Vetor` toda vez).

#### Bloco 1.3: Protótipos das Funções
```c
Vetor *vetor_criar(int capacidade);
int    vetor_adicionar(Vetor *v, int valor);
int    vetor_obter(Vetor *v, int i, int *saida);
void   vetor_destruir(Vetor *v);
```
- `Vetor *vetor_criar(int capacidade);`: avisa ao compilador que existe uma função que recebe um inteiro `capacidade` e devolve um ponteiro para `Vetor`.
- `int vetor_adicionar(Vetor *v, int valor);`: declara a função que recebe o ponteiro do vetor e um `valor`, devolvendo `int` (`1` se deu certo, `0` se falhou).
- `int vetor_obter(Vetor *v, int i, int *saida);`: declara a função que lê a posição `i` de `v` e grava o resultado no endereço apontado por `saida`, devolvendo `1` (sucesso) ou `0` (índice inválido).
- `void vetor_destruir(Vetor *v);`: declara a função sem retorno (`void`) responsável por liberar a memória do vetor.

---

### 2. Arquivo `vetor.c` (Implementação das Funções)

#### Bloco 2.1: Inclusão de Bibliotecas
```c
#include <stdlib.h>
#include "vetor.h"
```
- `#include <stdlib.h>`: inclui a biblioteca padrão necessária para usar `malloc`, `free` e `NULL`.
- `#include "vetor.h"`: inclui o cabeçalho local para que `vetor.c` conheça a `struct Vetor` e garanta que as assinaturas das funções batem com o `.h`.

#### Bloco 2.2: Função `vetor_criar`
```c
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
```
- `Vetor *vetor_criar(int capacidade) {`: inicia a função que cria um vetor na memória heap e devolve seu endereço.
- `if (capacidade <= 0) {`: verifica se a capacidade pedida é zero ou negativa (inválida).
- `return NULL;`: encerra a função retornando `NULL` para indicar falha se a capacidade for inválida.
- `Vetor *v = malloc(sizeof(Vetor));`: pede ao sistema memória suficiente para guardar uma `struct Vetor` e guarda o endereço no ponteiro `v`.
- `if (v == NULL) { return NULL; }`: testa se a alocação falhou (sem memória); se sim, retorna `NULL`.
- `v->dados = malloc((size_t)capacidade * sizeof(int));`: reserva memória para `capacidade` inteiros (`capacidade * tamanho de um int`) e guarda o endereço no campo `dados` de `v`. O `(size_t)` converte `capacidade` para o tipo sem sinal esperado por `malloc`.
- `if (v->dados == NULL) {`: testa se a reserva do array falhou.
- `free(v);`: como `v` já havia sido reservado antes, libera `v` para não causar vazamento de memória (*memory leak*).
- `return NULL;`: devolve `NULL` sinalizando que a criação falhou.
- `v->tamanho = 0;`: inicializa a quantidade de itens em uso como `0` (o vetor começa vazio).
- `v->capacidade = capacidade;`: registra no struct qual é a capacidade máxima reservada.
- `return v;`: devolve o ponteiro para o `Vetor` pronto para uso.

#### Bloco 2.3: Função `vetor_adicionar`
```c
int vetor_adicionar(Vetor *v, int valor) {
    if (v == NULL || v->tamanho == v->capacidade) {
        return 0;
    }

    v->dados[v->tamanho] = valor;
    v->tamanho += 1;
    return 1;
}
```
- `int vetor_adicionar(Vetor *v, int valor) {`: recebe o endereço do vetor `v` e o número `valor` a inserir.
- `if (v == NULL || v->tamanho == v->capacidade) {`: verifica se o ponteiro `v` é nulo **ou** se o vetor já atingiu o limite (`tamanho` igual à `capacidade`).
- `return 0;`: não grava nada e devolve `0` indicando que não foi possível adicionar.
- `v->dados[v->tamanho] = valor;`: escreve `valor` na próxima posição livre do array (como os índices vão de `0` até `tamanho - 1`, o índice `v->tamanho` é exatamente o próximo espaço vago).
- `v->tamanho += 1;`: aumenta em `1` o contador de elementos em uso.
- `return 1;`: devolve `1` indicando sucesso na inserção.

#### Bloco 2.4: Função `vetor_obter`
```c
int vetor_obter(Vetor *v, int i, int *saida) {
    if (v == NULL || saida == NULL || i < 0 || i >= v->tamanho) {
        return 0;
    }

    *saida = v->dados[i];
    return 1;
}
```
- `int vetor_obter(Vetor *v, int i, int *saida) {`: recebe o vetor `v`, o índice `i` desejado e um ponteiro `saida` onde o valor lido será depositado.
- `if (v == NULL || saida == NULL || i < 0 || i >= v->tamanho) {`: garante segurança verificando se `v` ou `saida` são nulos, ou se `i` está fora dos elementos válidos (`< 0` ou `>= tamanho`).
- `return 0;`: devolve `0` indicando que a leitura é inválida (não altera `*saida`).
- `*saida = v->dados[i];`: desreferencia o ponteiro `saida` (`*saida`) para gravar diretamente na variável do chamador o valor armazenado na posição `i`.
- `return 1;`: devolve `1` confirmando que o valor foi obtido com sucesso.

#### Bloco 2.5: Função `vetor_destruir`
```c
void vetor_destruir(Vetor *v) {
    if (v != NULL) {
        free(v->dados);
        free(v);
    }
}
```
- `void vetor_destruir(Vetor *v) {`: inicia a função de limpeza de memória.
- `if (v != NULL) {`: só executa os `free` se `v` não for nulo (evita acessar `v->dados` em um ponteiro `NULL`).
- `free(v->dados);`: libera **primeiro** o array interno de inteiros (se liberássemos `v` antes, perderíamos o endereço de `v->dados`).
- `free(v);`: libera em seguida a própria `struct Vetor`.

---

### 3. Arquivo `main.c` (Programa Principal)

#### Bloco 3.1: Cabeçalhos e Criação do Vetor
```c
#include <stdio.h>
#include "vetor.h"

int main(void) {
    Vetor *notas = vetor_criar(3);
    if (notas == NULL) {
        printf("sem memoria\n");
        return 1;
    }
```
- `#include <stdio.h>`: inclui a biblioteca padrão de entrada e saída para usar `printf`.
- `#include "vetor.h"`: traz a definição de `Vetor` e as funções declaradas no cabeçalho.
- `int main(void) {`: ponto de entrada do programa (`void` indica que não recebe argumentos da linha de comando).
- `Vetor *notas = vetor_criar(3);`: cria dinamicamente um vetor `notas` com capacidade para `3` inteiros.
- `if (notas == NULL) {`: verifica se houve erro de alocação ao criar o vetor.
- `printf("sem memoria\n");`: exibe uma mensagem de erro no terminal.
- `return 1;`: encerra o programa com código `1` (convenção para saída com erro).

#### Bloco 3.2: Inserção das Notas
```c
    int entradas[] = {7, 9, 5, 10};
    for (int i = 0; i < 4; i++) {
        if (vetor_adicionar(notas, entradas[i])) {
            printf("adicionou %d\n", entradas[i]);
        } else {
            printf("cheio! nao coube %d\n", entradas[i]);
        }
    }
```
- `int entradas[] = {7, 9, 5, 10};`: cria um array fixo com `4` valores de teste (um a mais que a capacidade `3`, para testar o limite).
- `for (int i = 0; i < 4; i++) {`: laço que percorre os índices `0`, `1`, `2` e `3` de `entradas`.
- `if (vetor_adicionar(notas, entradas[i])) {`: tenta adicionar `entradas[i]` em `notas`; como `1` é verdadeiro e `0` é falso em C, entra no `if` quando couber.
- `printf("adicionou %d\n", entradas[i]);`: imprime qual nota foi adicionada.
- `} else { printf("cheio! nao coube %d\n", entradas[i]); }`: quando `vetor_adicionar` retorna `0` (no 4º item, `10`), avisa que o vetor está cheio.

#### Bloco 3.3: Soma e Cálculo da Média
```c
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
```
- `int soma = 0;`: inicializa o acumulador da soma em `0`.
- `for (int i = 0; i < notas->tamanho; i++) {`: percorre apenas os elementos realmente armazenados (`0` até `tamanho - 1`).
- `int n;`: declara uma variável local para receber o valor de cada posição.
- `if (vetor_obter(notas, i, &n)) {`: passa o endereço de `n` (`&n`) para que a função preencha `n` com o elemento do índice `i`.
- `soma += n;`: soma o valor obtido ao acumulador `soma`.
- `if (notas->tamanho > 0) {`: evita divisão por zero caso nenhuma nota tenha sido adicionada.
- `printf("media: %.2f\n", (double)soma / notas->tamanho);`: converte `soma` para `double` (para a divisão não truncar a parte decimal) e imprime a média com 2 casas decimais (`%.2f`).

#### Bloco 3.4: Teste de Índice Inválido e Encerramento
```c
    int x;
    if (!vetor_obter(notas, 10, &x)) {
        printf("indice 10 invalido\n");
    }

    vetor_destruir(notas);
    return 0;
}
```
- `int x;`: variável auxiliar passada para `vetor_obter`.
- `if (!vetor_obter(notas, 10, &x)) {`: tenta acessar o índice `10` (que não existe); o operador `!` inverte o retorno `0` para verdadeiro.
- `printf("indice 10 invalido\n");`: confirma no terminal que o acesso fora do limite foi bloqueado com segurança.
- `vetor_destruir(notas);`: libera toda a memória dinâmica alocada para `notas`.
- `return 0;`: encerra o `main` retornando `0` (convenção de execução bem-sucedida).

---

## Como Compilar e Executar

### Usando `mingw32-make` (Windows) ou `make` (Linux/macOS)

```bash
# Compilar o programa principal em C (build/bin/programa.exe)
mingw32-make

# Compilar e executar o programa principal
mingw32-make run

# Compilar os utilitários auxiliares em C++ (build/bin/bench.exe e leitor.exe)
mingw32-make extras

# Executar o benchmark (C vs std::vector)
mingw32-make run-bench

# Executar o leitor de arquivo de notas (lendo data/notas.txt)
mingw32-make run-leitor

# Remover arquivos compilados em build/obj e build/bin
mingw32-make clean

# Ver resumo dos comandos
mingw32-make help
```

### Utilitários Auxiliares em C++

- **`extras/bench.cpp`**: usa `std::chrono::steady_clock` para comparar o tempo de alocação, inserção, leitura (`vetor_obter`) e liberação de `100000` elementos no `Vetor` em C contra `std::vector<int>` (com e sem `reserve`).
- **`extras/leitor.cpp`**: usa `std::ifstream`, `std::string` e `std::istringstream` para ler inteiros de `data/notas.txt` (ou outro arquivo passado por argumento, ignorando comentários `#` e aceitando espaços, vírgulas ou `;`), armazenando os valores no `Vetor` em C e exibindo média, menor e maior valor.

### Compilando manualmente com `gcc`

```bash
gcc -Wall -Wextra -Wpedantic -Iinclude src/main.c src/vetor.c -o build/bin/programa.exe
.\build\bin\programa.exe
```
