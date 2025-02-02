#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define rA 18
#define cA 16
#define rB 16
#define cB 18

int A[rA][cA];
int B[rB][cB];
int C[rA][cB];

typedef struct {
    int row;
    int col;
} ThreadData;

void *compute_Cij(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int row = data->row;
    int col = data->col;
    
    C[row][col] = 0;
    for (int k = 0; k < cA; k++) {
        C[row][col] += A[row][k] * B[k][col];
    }
    
    free(data);
    pthread_exit(NULL);
    return NULL;  // <-- Add this line to suppress the warning
}


int main() {
    // Initialize matrices A and B
    for (int i = 0; i < rA; i++) {
        for (int j = 0; j < cA; j++) {
            A[i][j] = i + 1 + j + 1;
        }
    }
    
    for (int i = 0; i < rB; i++) {
        for (int j = 0; j < cB; j++) {
            B[i][j] = i + 1 + 2 * (j + 1);
        }
    }
    
    pthread_t threads[rA][cB];
    
    // Create threads to compute each C[i][j]
    for (int i = 0; i < rA; i++) {
        for (int j = 0; j < cB; j++) {
            ThreadData *data = (ThreadData *)malloc(sizeof(ThreadData));
            data->row = i;
            data->col = j;
            pthread_create(&threads[i][j], NULL, compute_Cij, (void *)data);
        }
    }
    
    // Join all threads
    for (int i = 0; i < rA; i++) {
        for (int j = 0; j < cB; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }
    
    // Print diagonal elements of C
    printf("Diagonal elements of C:\n");
    for (int i = 0; i < rA; i++) {
        printf("%d ", C[i][i]);
    }
    printf("\n");
    
    return 0;
}
