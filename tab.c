#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 3
#define K 2
#define N 3

struct thread_data {
    int row;
    int col;
};

int A[M][K] = {{1, 4}, {2, 5}, {3, 6}};
int B[K][N] = {{8, 7, 6}, {5, 4, 3}};
int C[M][N];

void *matrix_multiply(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    int row = data->row;
    int col = data->col;

    // Calcula o elemento C[row][col]
    C[row][col] = 0;
    for (int k = 0; k < K; k++) {
        C[row][col] += (A[row][k] * B[k][col]);
    }

    free(data); // Libera a memória alocada para data
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[M * N];
    int thread_count = 0;

    // Cria threads para calcular os elementos de C
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            struct thread_data *data = (struct thread_data *)malloc(sizeof(struct thread_data));
            data->row = i;
            data->col = j;

            pthread_create(&threads[thread_count], NULL, matrix_multiply, (void *)data);
            thread_count++;
        }
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < M * N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprime a matriz resultante C
    printf("Matriz resultante C:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
