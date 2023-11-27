// Materia: Programación I, Paralelo 2

// Autor: Raquel Osorio Mamani

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023
 
// Número de ejericio: 4

// Problema planteado: Codifique un programa que cree un fichero para contener los datos relativos a los artículos de
// un almacén.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string fich1 = "almacen1.bin"; 
const string fich2 = "almacen2.bin"; 

struct A {
    int c; 
    string n;
    int e; 
    double p; 
};

bool cmp(const A& a, const A& b) {
    return a.c < b.c;
}

A get() {
    A nA;

    cout << "Ingrese el código del artículo (0 para finalizar): ";
    cin >> nA.c;

    if (nA.c != 0) {
        cin.ignore();  // Limpiar el buffer de entrada

        cout << "Ingrese el nombre del artículo: ";
        getline(cin, nA.n);

        cout << "Ingrese las existencias actuales: ";
        cin >> nA.e;

        cout << "Ingrese el precio: ";
        cin >> nA.p;
    }

    return nA;
}

void writeToFile(vector<A>& a, const string& filename) {
    sort(a.begin(), a.end(), cmp);

    ofstream file(filename, ios::binary | ios::app);  // Modo ios::app para añadir al final

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return;
    }

    for (const auto& aI : a) {
        file.write(reinterpret_cast<const char*>(&aI), sizeof(A));
    }

    file.close();

    cout << "Datos almacenados en el archivo " << filename << "." << endl;
}


void getDataAndWriteToFile(const string& filename) {
    vector<A> a;

    while (true) {
        A nA = get();

        if (nA.c == 0) {
            break;
        }

        a.push_back(nA);
    }

    // Dependiendo del archivo seleccionado, se escribirá en fich1 o fich2 con extensión .bin
    writeToFile(a, filename);
}

int main() {
    // Llenar el primer archivo
    cout << "Llenar el primer archivo:" << endl;
    getDataAndWriteToFile(fich1);

    // Llenar el segundo archivo
    cout << "Llenar el segundo archivo:" << endl;
    getDataAndWriteToFile(fich2);

    return 0;
}
