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

void preencher_linha(int matriz[M][N], int linha, int valor_inicial) {
  int i;
  for(i = 0; i < N; i++, valor_inicial++)
    matriz[linha][i] = valor_inicial;
}

int conjunto_existe(int* cont, int j) {
  if (j > *cont - 1) {
    printf("Erro: o conjunto %d nao foi criado!", j);
    return 0;
  }
  return 1;
}

int indice_esta_no_intervalo(int j, int* cont) {
  if (j < 0 || j > M - 1) {
    printf("Erro: digite um valor entre 0 e %d", *cont - 1);
    return 0;
  }
  return 1;
}

void mostrar_conjunto(int* cont, int conjuntos[M][N], int linha) {
  int i;

  /*
  if (linha > *cont - 1) {
    printf("Erro: o conjunto %d nao foi criado!", linha);
    return;
  }
  */
  
  if (!conjunto_existe(cont, linha)) return;
  
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
      return 1;
  return 0;
}

void inserir(int* cont, int conjuntos[M][N]) {
  int i, j, valor = 1;

  printf("Digite o indice do conjunto: ");
  scanf("%d", &j);

  /*
  if (j < 0 || j > M - 1) {
    printf("Erro: digite um valor entre 0 e %d", M - 1);
    return;
  }


  if (j > *cont - 1) {
    printf("Erro: o conjunto %d nao foi criado!", j);
    return;
  }
  */

  if (!indice_esta_no_intervalo(j, cont)) return;
  if (!conjunto_existe(cont, j)) return;
  
  for(i = 0; conjuntos[j][i] != 0; i++); // Coloca o índice i na primeira posição vazia.

  if (i < N) {
    printf("Digite os valores, um por vez:\n");
    for (; i < N && valor != 0; i++) {
      scanf("%d", &valor);
      int eh_valor_repetido = busca_sequencial(conjuntos, j, valor);
      if (valor && !eh_valor_repetido) {
	conjuntos[j][i] = valor;
      } else if (valor) {
	printf("Valor ja inserido. Digite outro valor\n");
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

void buscar_valor_matriz(int *cont, int conjuntos[M][N]) {
  int valor_procurado;
  printf("Digite o número inteiro procurado: ");
  scanf("%d", &valor_procurado);

  int encontrado = 0; // verifica se a função encontrar o número em alguma
                      // matriz muda para 1, se não continua 0

  for (int i = 0; i < *cont; i++) {
    //busca_sequencial(conjuntos, i, valor_procurado);
    if (busca_sequencial(conjuntos, i, valor_procurado) == 1) {
      printf("O valor %d foi encontrado no conjunto %d\n", valor_procurado, i);
      encontrado = 1;
    }
  }
  // se o número não existir em nenhum conjunto após a busca:
  if (encontrado == 0) {
    printf("O valor não pertence a nenhum conjunto. \n");
  }
}

void uniao_conjuntos(int *cont, int conjuntos[M][N]) {
  int i1, i2; // os índices que o usuário deve informar

  printf("Digite a linha do primeiro conjunto: \n");
  scanf("%d", &i1);

  printf("Digite a linha do segundo conjunto: \n");
  scanf("%d", &i2);

  int pos_coluna_nova = 0;

  if (i1 >= 0 && i1 < *cont && i2 >= 0 && i2 < *cont) {
    for (int j = 0; j < N && conjuntos[i1][j] != 0; j++) {

      // o cont aponta para a próxima linha vazia
      conjuntos[*cont][pos_coluna_nova] = conjuntos[i1][j];
      pos_coluna_nova++;
    }
    for (int j = 0; j < N && conjuntos[i2][j] != 0; j++) {
      int elemento = conjuntos[i2][j];
      if (!busca_sequencial(conjuntos, *cont, elemento)) {
        conjuntos[*cont][pos_coluna_nova] = elemento;
        pos_coluna_nova++;
      }
    }
    // adiciona o 0 no fim da nova linha para marcar o fim do conjunto
    conjuntos[*cont][pos_coluna_nova] = 0;

    (*cont)++;

    printf("Uniao realizada com sucesso na linha %d\n", *cont - 1);
  } else {
    printf("Erro: Uma ou ambas as linhas informadas são inválidas!\n");
    return;
  }
}

void remover_conjunto(int *cont, int conjuntos[M][N]) {
  int i, j, k, l1;

  printf("Digite a linha do conjunto a ser removido: ");
  scanf("%d", &l1);

  if (!indice_esta_no_intervalo(l1, cont)) return;
  if (!conjunto_existe(cont, l1)) return;

  for(j = l1; j < M - 1 && j < *cont; j++)
    for(k = 0; k < N; k++) {
      conjuntos[j][k] = conjuntos[j + 1][k];
      conjuntos[j + 1][k] = 0;
    }

  *cont = *cont - 1;
}

int main() {
  int conjuntos[M][N] = {0};
  // conta o número de conjuntos existentes
  int cont = M; // cont != 0 apenas para testes
  preencher_linha(conjuntos, 0, 1);
  preencher_linha(conjuntos, 1, 2);

  mostrar_todos_os_conjuntos(&cont, conjuntos);
  
  // mostrar_conjunto(&cont, conjuntos, 0);
  inserir(&cont, conjuntos);
  mostrar_todos_os_conjuntos(&cont, conjuntos);
  inserir(&cont, conjuntos);
  mostrar_todos_os_conjuntos(&cont, conjuntos);
  //  mostrar_conjunto(&cont, conjuntos, 0);
  //  mostrar_conjunto(&cont, conjuntos, 1);

  printf("Testando remocao de conjunto\n");
  mostrar_todos_os_conjuntos(&cont, conjuntos);
  remover_conjunto(&cont, conjuntos);
  printf("Cont: %d\n", cont);
  mostrar_todos_os_conjuntos(&cont, conjuntos);

  printf("Testando busca de valores ");
  buscar_valor_matriz(&cont, conjuntos);

  return 0;
}
