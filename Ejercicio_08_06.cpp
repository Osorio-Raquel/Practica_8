// Materia: Programación I, Paralelo 2

// Autor: Raquel Osorio Mamani

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023
 
// Número de ejericio: 6

// Problema planteado: Escriba un programa que tome como entrada el fichero del ejercicio 4 y una condición sobre el
// campo precio.

#include <iostream>
#include <fstream>

using namespace std;

const string fich1 = "almacen1.bin";
const string salidaFilename = "salida.dat";

struct Articulo {
    int codigo;
    string nombre;
    int existencias;
    double precio;
};

bool cumplirCondicion(const Articulo& articulo, double condicion) {

    return articulo.precio <= condicion;
}

int main() {
    ifstream fileIn(fich1, ios::binary);

    if (!fileIn.is_open()) {
        cerr << "Error al abrir el archivo de entrada." << endl;
        return 1;
    }

    ofstream fileOut(salidaFilename, ios::binary | ios::trunc);

    if (!fileOut.is_open()) {
        cerr << "Error al abrir el archivo de salida." << endl;
        fileIn.close();
        return 1;
    }

    double condicion;
    cout << "Ingrese la condición sobre el campo Precio: ";
    cin >> condicion;

    Articulo articulo;
    while (fileIn.read(reinterpret_cast<char*>(&articulo), sizeof(articulo))) {
        if (cumplirCondicion(articulo, condicion)) { // verificar que cumplan con la condicion
            fileOut.write(reinterpret_cast<const char*>(&articulo), sizeof(articulo));
        }
    }

    fileIn.close();
    fileOut.close();

    cout << "Proceso finalizado. Se ha creado el archivo " << salidaFilename << " con los artículos que cumplen la condición." << endl;

    return 0;
}
