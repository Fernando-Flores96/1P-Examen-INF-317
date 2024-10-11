#include <stdio.h>
#include <mpi.h>

#define N 7 // Tamaño del vector

int main(int argc, char **argv) {
    int procesador, cantidad;
	// Inicializamos los vectores
    int vector1[N] = {15,1,2,5,8,4,5}; 
    int vector2[N] = {3,1,7,5,2,10,7}; 
    int resultado[N];
    int impares[N / 2], pares[N / 2]; // Arreglos temporales para pares e impares

    // Inicio de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad);

    if (procesador == 0) {
        // Enviar posiciones impares a procesador 1
        MPI_Send(vector1, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vector2, N, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Enviar posiciones pares a procesador 2
        MPI_Send(vector1, N, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(vector2, N, MPI_INT, 2, 0, MPI_COMM_WORLD);

        // Recibir resultado de posiciones impares desde procesador 1
        MPI_Recv(impares, N / 2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Recibir resultado de posiciones pares desde procesador 2
        MPI_Recv(pares, N / 2, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Combinar los resultados de pares e impares
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) {
                resultado[i] = pares[i / 2]; // Pares
            } else {
                resultado[i] = impares[i / 2]; // Impares
            }
        }

        // Imprimir el vector resultado
        printf("Vector resultado de la suma: [");
        for (int i = 0; i < N; i++) {
            printf("%d ", resultado[i]);
        }
        printf("]\n");
    }

    if (procesador == 1) {
        // Recibir los vectores desde el procesador 0
        MPI_Recv(vector1, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vector2, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Sumar posiciones impares
        for (int i = 1; i < N; i += 2) {
            impares[i / 2] = vector1[i] + vector2[i];
        }

        // Enviar resultado de posiciones impares al procesador 0
        MPI_Send(impares, N / 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (procesador == 2) {
        // Recibir los vectores desde el procesador 0
        MPI_Recv(vector1, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vector2, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Sumar posiciones pares
        for (int i = 0; i < N; i += 2) {
            pares[i / 2] = vector1[i] + vector2[i];
        }

        // Enviar resultado de posiciones pares al procesador 0
        MPI_Send(pares, N / 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
