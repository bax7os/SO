
#include <stdio.h>
#include <stdlib.h>


struct thread_data {
    int row;
    int col;
}thread_data;
#define M 3
#define K 2
#define N 3

int A [M][K] = { {1,4}, {2,5}, {3,6} };
int B [K][N] = { {8,7,6}, {5,4,3} };
int C [M][N];
int i, j;
for (i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
        thread_data *data = (thread_data *)malloc(sizeof(thread_data));
        data->row = i;
        data->col = j;
        // Crie a thread e passe data como argumento
    }
}
for (int i = 0; i < (M * N); i++) {
    pthread_join(threads[i], NULL);
}
