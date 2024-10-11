#include <stdio.h>
#include <omp.h>

int main() {
    int n = 10; // Número de términos de la serie de Fibonacci
    int fibonacci[n]; // Array para almacenar la serie
    int i;

    // Inicializar los primeros dos términos
    fibonacci[0] = 0;
    fibonacci[1] = 1;

    // Usamos OpenMP para calcular el resto de la serie de Fibonacci
    #pragma omp parallel shared(fibonacci) private(i)
    {
        // Cada hilo va a calcular un número en la serie
        #pragma omp for
        for (i = 2; i < n; i++) {
            // Cada hilo calcula el siguiente número en la serie
            fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        }
    }

    // Imprimir la serie de Fibonacci
    printf("Serie de Fibonacci: ");
    for (i = 0; i < n; i++) {
        printf("%d ", fibonacci[i]);
    }
    printf("\n");

    return 0;
}