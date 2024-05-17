#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define M 3
#define K 2
#define N 3

int A[M][K] = { {1,4}, {2,5}, {3,6} };
int B[K][N] = { {8,7,6}, {5,4,3} };
int C[M][N];

struct v {
    int i; /* linha */
    int j; /* coluna */
};

/* calculando o produto das matrizes */
void *produto(void *param) {
    struct v *data = param;
    int sum = 0;

    for(int n = 0; n< K; n++){
        sum += A[data->i][n] * B[n][data->j];
    }


    C[data->i][data->j] = sum;

    /* finalizando a thread, 0 indica que foi finalizada com sucesso */
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    pthread_t workers[M][N]; /* matriz de identificadores de thread */
    struct v *data; /* responsável para passar os indices das linhas e colunas para as threads */


    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {

            data = (struct v *) malloc(sizeof(struct v));
            /* atribuição dos indices */
            data->i = i;
            data->j = j;
            /* criação da nova thread */
            pthread_create(&workers[i][j], NULL, produto, data);
        }
    }

    /* espera a finalização de todas as threads */
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
        /* bloqueia a execução do programa principal até que a thread correspondente termine */
            pthread_join(workers[i][j], NULL);
        }
    }

/* imprimime a matriz C resultante */
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
