#include <stdio.h>
#include <mpi.h>

#define M 3 // Número de filas de A
#define N 4 // Número de columnas de A (y filas de B)
#define P 2 // Número de columnas de B

int main(int argc, char **argv) {
    int rank, size;
    int A[M][N], B[N][P], C[M][P]; // Matrices A, B y resultado C
    int filaA[N], resultadoFila[P];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Inicializar matriz A
        printf("Matriz A (%d x %d):\n", M, N);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j; // Ejemplo de inicialización
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }

        // Inicializar matriz B
        printf("Matriz B (%d x %d):\n", N, P);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                B[i][j] = i + j; // Ejemplo de inicialización
                printf("%d ", B[i][j]);
            }
            printf("\n");
        }
    }

    // Distribuir la matriz B a todos los procesos
    MPI_Bcast(&B, N * P, MPI_INT, 0, MPI_COMM_WORLD);

    // Enviar filas de la matriz A a cada procesador
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            if (i - 1 < M) {
                MPI_Send(A[i - 1], N, MPI_INT, i, 0, MPI_COMM_WORLD); // Enviar una fila de A
            }
        }
        // Calcular la primera fila para el procesador 0
        for (int j = 0; j < P; j++) {
            resultadoFila[j] = 0;
            for (int k = 0; k < N; k++) {
                resultadoFila[j] += A[0][k] * B[k][j];
            }
        }
        for (int j = 0; j < P; j++) {
            C[0][j] = resultadoFila[j];
        }
    } else {
        // Recibir una fila de A
        if (rank - 1 < M) {
            MPI_Recv(filaA, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // Multiplicar la fila recibida de A por la matriz B
            for (int j = 0; j < P; j++) {
                resultadoFila[j] = 0;
                for (int k = 0; k < N; k++) {
                    resultadoFila[j] += filaA[k] * B[k][j];
                }
            }
            // Enviar la fila resultado al procesador 0
            MPI_Send(resultadoFila, P, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    // Recibir las filas resultantes en el procesador 0 y ensamblar la matriz C
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            if (i - 1 < M) {
                MPI_Recv(C[i], P, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        // Imprimir la matriz resultado C
        printf("Matriz resultado C (%d x %d):\n", M, P);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < P; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
