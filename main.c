#include <stdio.h>

#define M 5
#define N 10

void inicializar_matriz(int matriz[M][N]) {
  int i, j;
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      matriz[i][j] = 0;
    }
  }
}

void mostrar_conjunto(int* cont, int conjuntos[M][N], int linha) {
  int i;

  if (linha > *cont - 1) {
    printf("Erro: o conjunto %d nao foi criado!", linha);
    return;
  }
  printf("\nConjunto %d = ", linha);
  if (conjuntos[linha][0]) {
    for (i = 0; i < N && conjuntos[linha][i] != 0; i++)
      printf("%d ", conjuntos[linha][i]);
  } else
    printf("vazio");
  //printf("\n");
}

int busca_sequencial(int matriz[M][N], int linha, int valor /*, int colunas_preenchidas*/) {
                     
  int j; // coluna

  for (j = 0; matriz[linha][j] != 0 /*j < colunas_preenchidas*/; j++)
    if (matriz[linha][j] == valor)
      return 1; // encontrou o número repetido
  return 0; // não há números repetidos
}

void inserir(int* cont, int conjuntos[M][N]) {
  int i, j, valor = 1;

  printf("Digite o indice do conjunto: ");
  scanf("%d", &j);

  if (j < 0 || j > M - 1) {
    printf("Erro: digite um valor entre 0 e %d", M - 1);
    return;
  }

  if (j > *cont - 1) {
    printf("Erro: o conjunto %d nao foi criado!", j);
    return;
  }

  for(i = 0; conjuntos[j][i] != 0; i++); // Coloca o índice i na primeira posição vazia.

  if (i < N) {
    printf("Digite os valores, um por vez:\n");
    for (; i < N && valor != 0; i++) {
      scanf("%d", &valor);
      int eh_valor_repetido = busca_sequencial(conjuntos, j, valor);
      if (valor && !eh_valor_repetido) {
	conjuntos[j][i] = valor;
      } else if (valor) {
	printf("Valor ja inserido. Digito outro valor\n");
	i--;
      }
    }
  } else
      printf("O conjunto %d esta cheio!\n", j);
}

void mostrar_todos_os_conjuntos(int* cont, int conjuntos[M][N]) {
  int i;

  for (i = 0; i < *cont; i++)
    mostrar_conjunto(cont, conjuntos, i);

  if (!*cont)
    printf("Nenhum conjunto foi criado\n");
  else
    printf("\n");
  
}

int main() {
  int conjuntos[M][N] = {0};
  int cont = 2; // cont != 0 apenas para testes
  
  conjuntos[0][0] = 1;
  conjuntos[1][0] = 2;

  mostrar_todos_os_conjuntos(&cont, conjuntos);
  
  // mostrar_conjunto(&cont, conjuntos, 0);
  inserir(&cont, conjuntos);
  mostrar_todos_os_conjuntos(&cont, conjuntos);
  inserir(&cont, conjuntos);
  mostrar_todos_os_conjuntos(&cont, conjuntos);
  //  mostrar_conjunto(&cont, conjuntos, 0);
  //  mostrar_conjunto(&cont, conjuntos, 1);
  
  return 0;
}


