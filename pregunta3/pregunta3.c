#include <stdio.h>

void suma(int a, int b, int *res) {
    *res = a + b; 
}

void resta(int a, int b, int *res) {
    *res = a - b; 
}

void multiplicacion(int a, int b, int *res) {
    *res = a * b; 
}

void division(int a, int b, float *resDiv) {
    if (b != 0) {
        *resDiv = (float)a / b; 
    } else {
        printf("No se puede realizar la división por cero.\n");
    }
}

int main() {
    int a, b, res; 
    float resDiv; 

    printf("Introduzca a: ");
    scanf("%d", &a);
    printf("Introduzca b: ");
    scanf("%d", &b);
    
    suma(a, b, &res);
    printf("Suma: %d\n", res);
    
    resta(a, b, &res);
    printf("Resta: %d\n", res);
    
    multiplicacion(a, b, &res);
    printf("Multiplicación: %d\n", res);
    
    division(a, b, &resDiv);
    if (b != 0) { 
        printf("División: %.2f\n", resDiv);
    }

    return 0; 
}

