#include <stdio.h>

int suma(int a, int b) {
    return a + b;
}

int resta(int a, int b) {
    return a - b;
}

int multiplicacion(int a, int b) {
    return a * b;
}

float division(int a, int b) {
    if (b != 0) {
        return (float)a / b;
    } else {
        printf("No se puede hacer la división por cero \n");
        return 0;
    }
}

int main() {
    int a = 10; 
    int b = 2;  
    int c;
    float d;
    c = suma(a, b);
    printf("Suma: %d + %d = %d\n", a, b, c);
    c = resta(a, b);
    printf("Resta: %d - %d = %d\n", a, b, c);
    c = multiplicacion(a, b);
    printf("Multiplicación: %d * %d = %d\n", a, b, c);
    d = division(a, b);
    printf("División: %d / %d = %.2f\n", a, b, d); 
}

