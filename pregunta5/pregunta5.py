import multiprocessing

def calcular_pi_parcial(rango, tamaño):
    pi_local = 0.0
    for n in range(rango, 1000000, tamaño): 
        signo = 1 if n % 2 == 0 else -1
        denominador = 2 * n + 1
        pi_local += signo * 1.0 / denominador
    return pi_local

if __name__ == "__main__":
    tamanio = max(3, multiprocessing.cpu_count())  # Usar al menos 3 procesos
    pool = multiprocessing.Pool(processes=tamanio)

    # Dividimos el trabajo entre los procesos
    resultados = pool.starmap(calcular_pi_parcial, [(rango, tamanio) for rango in range(tamanio)])
    
    # Sumamos los resultados parciales
    pi = sum(resultados)

    # Multiplicamos por 4 para obtener la aproximación final de π
    pi *= 4
    print("Valor aproximado de pi:", pi)