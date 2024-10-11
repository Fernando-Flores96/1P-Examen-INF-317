using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace biblioteca
{
    public class Funciones
    {
        // Método para determinar si un carácter es un operador
        public static bool veriOperador(char c)
        {
            return c == '+' || c == '-' || c == '*' || c == '/';
        }

        // Método para determinar la precedencia de los operadores
        public static int Precedencia(char op)
        {
            switch (op)
            {
                case '+':
                case '-':
                    return 1;
                case '*':
                case '/':
                    return 2;
                default:
                    return 0;
            }
        }

        // Método para convertir infijo a prefijo
        public static string infijo_a_Prefijo(string infijo)
        {
            // Invertir la cadena infija
            char[] infijoInvertido = infijo.ToCharArray();
            Array.Reverse(infijoInvertido);
            string infijoReverso = new string(infijoInvertido);

            Stack<char> pila = new Stack<char>();
            string prefijo = "";
            int i = 0;

            while (i < infijoReverso.Length)
            {
                char c = infijoReverso[i];

                if (c == ' ')
                {
                    i++;
                    continue;
                }

                // Leer número completo
                if (char.IsDigit(c))
                {
                    while (i < infijoReverso.Length && (char.IsDigit(infijoReverso[i]) || infijoReverso[i] == '.'))
                    {
                        prefijo += infijoReverso[i];
                        i++;
                    }
                    prefijo += ' '; // Separar número
                    continue; // Saltar al siguiente ciclo
                }

                // Manejar ()
                if (c == ')')
                {
                    pila.Push(c);
                }
                else if (c == '(')
                {
                    while (pila.Count > 0 && pila.Peek() != ')')
                    {
                        prefijo += pila.Pop() + " ";
                    }
                    pila.Pop(); // quitar ')'
                }
                else if (veriOperador(c))
                {
                    while (pila.Count > 0 && Precedencia(pila.Peek()) > Precedencia(c))
                    {
                        prefijo += pila.Pop() + " ";
                    }
                    pila.Push(c);
                }

                i++;
            }

            // Desapilar todos los operadores restantes
            while (pila.Count > 0)
            {
                prefijo += pila.Pop() + " ";
            }

            // Invertir la expresión prefija antes de retornarla
            char[] prefijoInvertido = prefijo.ToCharArray();
            Array.Reverse(prefijoInvertido);
            return new string(prefijoInvertido).Trim(); // Remover espacio final
        }

        // Método para evaluar la expresión en notación prefija
        public static double EvaluarPrefijo(string prefijo)
        {
            Stack<double> pila = new Stack<double>();
            string[] datos = prefijo.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries).Reverse().ToArray();

            foreach (string dato in datos)
            {
                double num;
                if (double.TryParse(dato, out num))
                {
                    pila.Push(num); // Agregar el número
                }
                else if (veriOperador(dato[0])) // Manejar operador
                {
                    if (pila.Count < 2)
                    {
                        throw new InvalidOperationException("No hay suficientes operandos en la pila para realizar la operación.");
                    }

                    double a = pila.Pop(); // El primer operando
                    double b = pila.Pop(); // El segundo operando
                    double res = AplicarOperacion(a, b, dato[0]);
                    pila.Push(res); // Apilar el resultado
                }
                else
                {
                    throw new InvalidOperationException("Token desconocido: " + dato);
                }
            }

            if (pila.Count != 1)
            {
                throw new InvalidOperationException("La expresión prefija es inválida.");
            }

            return pila.Pop(); // Resultado final
        }

        // Método para realizar la operación
        public static double AplicarOperacion(double a, double b, char op)
        {
            switch (op)
            {
                case '+':
                    return a + b;
                case '-':
                    return a - b;
                case '*':
                    return a * b;
                case '/':
                    if (b == 0)
                    {
                        throw new DivideByZeroException("División por cero.");
                    }
                    return a / b;
                default:
                    throw new InvalidOperationException("Operador desconocido");
            }
        }
    }

}
