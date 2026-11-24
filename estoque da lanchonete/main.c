#include <stdio.h>

typedef struct {
  int codigo;
  int quantidade;
  float preco;
} Produto;

// Imprime uma linha por produto: Cod 1 | qtd 10 | R$ 5.50
void listar(Produto estoque[], int n) {
  for (int i = 0; i < n; i++) {
    printf("Cod %d | qtd %d | R$ %.2f\n", estoque[i].codigo,
           estoque[i].quantidade, estoque[i].preco);
  }
}

// Soma (quantidade * preco) de todos os produtos e devolve o total
float valor_total(Produto estoque[], int n) {
  float total = 0;
  for (int i = 0; i < n; i++) {
    total = total + (estoque[i].quantidade * estoque[i].preco);
    printf("%d", total);
  }
}
se vender recebesse Produto p(sem *), a quantidade do produto
    1 no estoque final seria

    // Tenta vender qtd unidades do produto apontado por p
    int vender(Produto *p, int qtd) {
  if (p->quantidade >= qtd) {
    p->quantidade = p->quantidade - qtd;
    return 1;

  } else {
    return 0;
  }
}

int main(void) {
  Produto estoque[3] = {{1, 10, 5.50}, // codigo, quantidade, preco
                        {2, 4, 8.00},
                        {3, 0, 12.90}};

  printf("--- Estoque inicial ---\n");
  listar(estoque, 3);
  printf("Valor total: R$ %.2f\n", valor_total(estoque, 3));

  printf("\n--- Vendas ---\n");
  if (vender(&estoque[0], 3))
    printf("Venda ok: produto 1, qtd 3\n");
  else
    printf("Sem estoque: produto 1, qtd 3\n");
  if (vender(&estoque[1], 5))
    printf("Venda ok: produto 2, qtd 5\n");
  else
    printf("Sem estoque: produto 2, qtd 5\n");
  if (vender(&estoque[2], 1))
    printf("Venda ok: produto 3, qtd 1\n");
  else
    printf("Sem estoque: produto 3, qtd 1\n");

  printf("\n--- Estoque final ---\n");
  listar(estoque, 3);
  printf("Valor total: R$ %.2f\n", valor_total(estoque, 3));

  return 0;
}
