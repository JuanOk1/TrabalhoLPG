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

int busca_sequencial(int matriz[M][N], int linha, int valor,
                     int colunas_preenchidas) {
  int j; // coluna

  for (j = 0; j < colunas_preenchidas; j++)
    if (matriz[M][j] == valor) {
      return 1; // encontrou o número repetido
    }
}
else {
  return 0; // não há números repetidos
}

int main() { return 0; }
