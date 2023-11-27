// Materia: Programación I, Paralelo 2

// Autor: Raquel Osorio Mamani

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023
 
// Número de ejericio: 8

// Problema planteado: Escribir un programa que genere a partir de un fichero de entrada que contiene una tabla de
// números reales otro fichero de salida

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Función para leer datos desde la consola
vector<vector<double>> leerDatosConsola(int num_filas, int num_columnas) {
    vector<vector<double>> datos(num_filas, vector<double>(num_columnas));
    double numero;

    cout << "Ingrese los datos:" << endl;
    for (int i = 0; i < num_filas; ++i) {
        for (int j = 0; j < num_columnas; ++j) {
            cin >> numero;
            datos[i][j] = numero;
        }
    }

    return datos;
}

// Función para escribir datos en un archivo binario con información de filas y columnas
void escribirDatosBinario(const string& nombre_archivo, const vector<vector<double>>& datos, int num_filas, int num_columnas) {
    ofstream archivo_salida(nombre_archivo, ios::binary);

    if (!archivo_salida.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de salida '" << nombre_archivo << "'." << endl;
        return;
    }

    // Escribir el número de filas y columnas al principio del archivo
    archivo_salida.write(reinterpret_cast<const char*>(&num_filas), sizeof(int));
    archivo_salida.write(reinterpret_cast<const char*>(&num_columnas), sizeof(int));

    // Escribir los datos en el archivo
    for (const auto& fila : datos) {
        for (double valor : fila) {
            archivo_salida.write(reinterpret_cast<const char*>(&valor), sizeof(double));
        }
    }

    archivo_salida.close();
    cout << "Datos escritos en '" << nombre_archivo << "'." << endl;
}

int main() {
    // Solicitar al usuario los tamaños de filas y columnas
    int num_filas, num_columnas;

    cout << "Ingrese el número de filas: ";
    cin >> num_filas;

    cout << "Ingrese el número de columnas: ";
    cin >> num_columnas;

    // Leer datos desde la consola
    vector<vector<double>> datos = leerDatosConsola(num_filas, num_columnas);

    // Escribir datos en el archivo binario con información de filas y columnas
    string nombre_archivo_salida = "DATOS.BIN";
    escribirDatosBinario(nombre_archivo_salida, datos, num_filas, num_columnas);

    return 0;
}
