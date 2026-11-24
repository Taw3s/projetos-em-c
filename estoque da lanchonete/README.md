# Projeto: Estoque da Lanchonete

Programa em C para controlar o estoque de uma lanchonete, realizar vendas com validação de quantidade e calcular o valor total em estoque.

## Estrutura da pasta

- `main.c` — Arquivo inicial da **Fase 1** (com `struct Produto`, `main` pronto e espaço para implementar as 3 funções).
- `Makefile` — Atalhos de compilação e execução com `gcc` / `mingw32-make`.
- `build/` — Onde o executável (`lanchonete.exe`) será gerado.

## Como compilar e executar

Dentro da pasta `estoque da lanchonete`:

```powershell
# Compilar e executar com Makefile
mingw32-make run

# Ou apenas compilar
mingw32-make

# Ou direto com gcc
gcc -std=c17 -Wall -Wextra -g main.c -o build/lanchonete.exe
.\build\lanchonete.exe
```

## Fase 1 — O que implementar em `main.c`

1. `void listar(Produto estoque[], int n)` — Imprime cada produto no formato: `Cod 1 | qtd 10 | R$ 5.50`
2. `float valor_total(Produto estoque[], int n)` — Soma `quantidade * preco` de todos os produtos e retorna `float`.
3. `int vender(Produto *p, int qtd)` — Se `p->quantidade >= qtd`, desconta `qtd` e retorna `1`; senão, não altera e retorna `0`.

### Saída esperada

```text
--- Estoque inicial ---
Cod 1 | qtd 10 | R$ 5.50
Cod 2 | qtd 4 | R$ 8.00
Cod 3 | qtd 0 | R$ 12.90
Valor total: R$ 87.00

--- Vendas ---
Venda ok: produto 1, qtd 3
Sem estoque: produto 2, qtd 5
Sem estoque: produto 3, qtd 1

--- Estoque final ---
Cod 1 | qtd 7 | R$ 5.50
Cod 2 | qtd 4 | R$ 8.00
Cod 3 | qtd 0 | R$ 12.90
Valor total: R$ 70.50
```

### Pergunta antes de rodar

Se `vender` recebesse `Produto p` (sem `*`), a quantidade do produto 1 no estoque final seria **A) 7** ou **B) 10**? Escolha e escreva o motivo em uma frase.

## Próximas fases

- **Fase 2:** Nome do produto (strings em C).
- **Fase 3:** Repor estoque.
- **Fase 4:** Estoque dinâmico com `Vetor` e `malloc`.
