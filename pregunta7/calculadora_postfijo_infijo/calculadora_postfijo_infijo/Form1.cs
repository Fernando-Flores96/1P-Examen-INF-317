using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
// Importar el namespace de la biblioteca
using biblioteca;

namespace calculadora_postfijo_infijo
{
    public partial class Form1 : Form
    {
        double res;
        string textogenerado;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            res = 0;
            resultado.Text = res.ToString();
            textogenerado = "";
        }

        private void composicion(object sender, EventArgs e)
        {
            textogenerado += ((Button)sender).Text;
            texto.Text = textogenerado;
        }

        private void button17_Click(object sender, EventArgs e)
        {
            // Eliminar el último carácter
            if (textogenerado.Length > 0)
                textogenerado = textogenerado.Remove(textogenerado.Length - 1);
            mostrar();
        }

        private void button19_Click(object sender, EventArgs e)
        {
            // Limpiar todo
            textogenerado = ""; // Lo que se genera
            res = 0; // La respuesta final de la operación
            texto.Text = ""; // Lo que se muestra en el resultado
            mostrar();
        }

        private void mostrar()
        {
            texto.Text = textogenerado;
            resultado.Text = res.ToString();
        }

        private void button18_Click(object sender, EventArgs e)
        {
            // Usar la clase Funciones desde la biblioteca
            string textoPrefijo = Funciones.infijo_a_Prefijo(textogenerado); // Cambia Class por Funciones
            res = Funciones.EvaluarPrefijo(textoPrefijo); // Cambia Class por Funciones
            mostrar();
        }

        private void label1_Click(object sender, EventArgs e)
        {
            // Este método parece estar vacío, puedes eliminarlo si no lo usas
        }
    }
}
