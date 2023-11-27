// Materia: Programación I, Paralelo 2

// Autor: Raquel Osorio Mamani

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023
 
// Número de ejericio: 9

// Problema planteado: hallar la suma horizontal y vertical y grabar la tabla y los resultados en otro fichero de texto o binario según se introduzca por pantalla. 

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Función para leer la tabla desde un archivo binario y obtener el número de filas y columnas
vector<vector<double>> leerDatosBinario(const string& nombre_archivo, int& num_filas, int& num_columnas) {
    ifstream archivo_entrada(nombre_archivo, ios::binary);

    if (!archivo_entrada.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de entrada '" << nombre_archivo << "'." << endl;
        exit(1);
    }

    // Leer el número de filas y columnas desde el archivo
    archivo_entrada.read(reinterpret_cast<char*>(&num_filas), sizeof(int));
    archivo_entrada.read(reinterpret_cast<char*>(&num_columnas), sizeof(int));

    // Crear la tabla de datos
    vector<vector<double>> datos(num_filas, vector<double>(num_columnas));

    // Leer los datos desde el archivo
    for (int i = 0; i < num_filas; ++i) {
        for (int j = 0; j < num_columnas; ++j) {
            archivo_entrada.read(reinterpret_cast<char*>(&datos[i][j]), sizeof(double));
        }
    }

    archivo_entrada.close();
    return datos;
}

// Función para calcular la suma horizontal y vertical
void calcularSumas(const vector<vector<double>>& datos, int num_filas, int num_columnas, vector<double>& suma_horizontal, vector<double>& suma_vertical) {
    suma_horizontal.resize(num_filas, 0.0);
    suma_vertical.resize(num_columnas, 0.0);

    for (int i = 0; i < num_filas; ++i) {
        for (int j = 0; j < num_columnas; ++j) {
            suma_horizontal[i] += datos[i][j];
            suma_vertical[j] += datos[i][j];
        }
    }
}

// Función para escribir la tabla y los resultados en un archivo de texto
void escribirResultados(const string& nombre_archivo, const vector<vector<double>>& datos, const vector<double>& suma_horizontal, const vector<double>& suma_vertical) {
    ofstream archivo_salida(nombre_archivo);

    if (!archivo_salida.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de salida '" << nombre_archivo << "'." << endl;
        exit(1);
    }

    archivo_salida << "Tabla de datos:" << endl;
    for (const auto& fila : datos) {
        for (double valor : fila) {
            archivo_salida << valor << "\t";
        }
        archivo_salida << endl;
    }

    archivo_salida << "\nSuma horizontal:" << endl;
    for (double suma : suma_horizontal) {
        archivo_salida << suma << "\t";
    }

    archivo_salida << "\n\nSuma vertical:" << endl;
    for (double suma : suma_vertical) {
        archivo_salida << suma << "\t";
    }

    archivo_salida.close();
    cout << "Resultados escritos en '" << nombre_archivo << "'." << endl;
}

int main() {
    // Leer la tabla desde el archivo binario y obtener el número de filas y columnas
    string nombre_archivo_entrada = "DATOS.BIN";
    int num_filas, num_columnas;
    vector<vector<double>> datos = leerDatosBinario(nombre_archivo_entrada, num_filas, num_columnas);

    // Calcular la suma horizontal y vertical
    vector<double> suma_horizontal, suma_vertical;
    calcularSumas(datos, num_filas, num_columnas, suma_horizontal, suma_vertical);

    // Escribir la tabla y los resultados en un archivo de texto
    string nombre_archivo_salida = "resultados.txt";
    escribirResultados(nombre_archivo_salida, datos, suma_horizontal, suma_vertical);

    return 0;
}
