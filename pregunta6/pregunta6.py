def fibonacci(n):
    # Creamos un vector (lista) para almacenar los términos de Fibonacci
    fib = [0, 1]  # Los dos primeros términos de la serie
    
    for i in range(2, n):
        siguiente_fib = fib[i - 1] + fib[i - 2]  
        fib.append(siguiente_fib)  
    
    return fib 

n = int(input("Introduzca el número de términos de Fibonacci a calcular: "))
serie_fibonacci = fibonacci(n)

print("Serie de Fibonacci hasta el término", n, ":", serie_fibonacci)