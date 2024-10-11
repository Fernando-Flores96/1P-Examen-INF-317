#include <stdio.h>

void calcular_pi_iterativo(int n, float *resultado) {
    float pi = 0.0;
    for (int i = 0; i < n; i++) {
        pi += (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
    }
    *resultado = 4 * pi; 
}

float calcular_pi_recursivo(int n, int i) {
    if (i >= n) {
        return 0; 
    }
    float term = (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
    return term + calcular_pi_recursivo(n, i + 1); 
}


int main() {
    int n; 
    float pi_iterativo, pi_recursivo;

    printf("Introduzca el número de términos para calcular π: ");
    scanf("%d", &n);

    calcular_pi_iterativo(n, &pi_iterativo);
    printf("Valor de π (iterativo) con %d términos: %.6f\n", n, pi_iterativo);

    pi_recursivo = calcular_pi_recursivo(n, 0);
    printf("Valor de π (recursivo) con %d términos: %.6f\n", n, 4 * pi_recursivo);
    return 0; 
}
