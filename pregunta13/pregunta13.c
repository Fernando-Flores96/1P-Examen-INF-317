#include <stdio.h>
#include <mpi.h>
#include <string.h>

#define N 5 // Tamaño del vector de cadenas
#define MAXLEN 100 // Longitud máxima de las cadenas

int main(int argc, char **argv) {
    int procesador, cantidad;
    char vector[N][MAXLEN] = {"Feliz", "Materia", "Rojo", "Lluvia", "Sol"}; // Vector de cadenas
    char pares[(N + 1) / 2][MAXLEN], impares[N / 2][MAXLEN]; // Aseguramos que pares e impares tengan el tamaño adecuado

    // Inicio de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad);

    if (procesador == 0) {
        // Enviar posiciones pares al procesador 1
        for (int i = 0; i < N; i += 2) {
            MPI_Send(vector[i], MAXLEN, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        }

        // Enviar posiciones impares al procesador 2
        for (int i = 1; i < N; i += 2) {
            MPI_Send(vector[i], MAXLEN, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
        }
    }

    if (procesador == 1) {
        // Recibir y desplegar las posiciones pares
        printf("Procesador 1 (pares):{");
        for (int i = 0; i < (N + 1) / 2; i++) {
            MPI_Recv(pares[i], MAXLEN, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", pares[i]);
            if (i < (N + 1) / 2 - 1) {
                printf(","); // Añadir coma entre elementos
            }
        }
        printf("}\n"); // Cerrar las llaves al final
    }

    if (procesador == 2) {
        // Recibir y desplegar las posiciones impares
        printf("Procesador 2 (impares):{");
        for (int i = 0; i < N / 2; i++) {
            MPI_Recv(impares[i], MAXLEN, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", impares[i]);
            if (i < N / 2 - 1) {
                printf(","); // Añadir coma entre elementos
            }
        }
        printf("}\n"); // Cerrar las llaves al final
    }

    MPI_Finalize();
    return 0;
}
