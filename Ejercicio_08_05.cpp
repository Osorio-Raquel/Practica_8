// Materia: Programación I, Paralelo 2

// Autor: Raquel Osorio Mamani

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023
 
// Número de ejericio: 5

// Problema planteado: Escriba un programa que dados dos ficheros generados por el programa anterior y ordenados
// genere un tercer fichero que sea el resultado de mezclar de formar ordenada los dos primeros. 

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const string fich1 = "almacen1.bin"; 
const string fich2 = "almacen2.bin";
const string fich3 = "almacen3.bin"; 

struct Articulo {
    int c;
    string n; 
    int e; 
    double p; 
};

bool cmp(const Articulo& a, const Articulo& b) {
    return a.c < b.c;
}

void mergeAndWriteToFile(const string& filename1, const string& filename2, const string& resultFilename) {
    vector<Articulo> a1, a2, merged;

    ifstream file1(filename1, ios::binary);
    ifstream file2(filename2, ios::binary);

    if (!file1.is_open() || !file2.is_open()) {
        cerr << "Error al abrir uno de los archivos de entrada." << endl;
        return;
    }

    Articulo item;
    while (file1.read(reinterpret_cast<char*>(&item), sizeof(item))) {
        a1.push_back(item);
    }

    while (file2.read(reinterpret_cast<char*>(&item), sizeof(item))) {
        a2.push_back(item);
    }

    file1.close();
    file2.close();

    // Fusionar y ordenar
    merged.reserve(a1.size() + a2.size());
    merged.insert(merged.end(), a1.begin(), a1.end());
    merged.insert(merged.end(), a2.begin(), a2.end());
    sort(merged.begin(), merged.end(), cmp);

    // Escribir en el tercer archivo
    ofstream resultFile(resultFilename, ios::binary | ios::trunc);  

    if (!resultFile.is_open()) {
        cerr << "Error al abrir el archivo de salida." << endl;
        return;
    }

    for (const auto& aI : merged) {
        resultFile.write(reinterpret_cast<const char*>(&aI), sizeof(Articulo));
    }

    resultFile.close();

    cout << "Datos almacenados en el archivo " << resultFilename << "." << endl;
}

void displayDataFromFile(const string& filename) {
    ifstream readF(filename, ios::binary);

    if (!readF.is_open()) {
        cerr << "Error al abrir el archivo " << filename << " para lectura." << endl;
        return;
    }

    Articulo item;
    cout << "\nDatos guardados en " << filename << ":\n";
    while (readF.read(reinterpret_cast<char*>(&item), sizeof(item))) {
        cout << "Código: " << item.c << ", Nombre: " << item.n << ", Existencias: " << item.e << ", Precio: " << item.p << endl;
    }

    readF.close();
}

int main() {
    mergeAndWriteToFile(fich1, fich2, fich3);
    displayDataFromFile(fich3);
    return 0;
}
