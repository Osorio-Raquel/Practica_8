// Materia: Programación I, Paralelo 2

// Autor: Raquel Osorio Mamani

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023
 
// Número de ejericio:3

// Problema planteado: Amplíe el programa anterior que procesa clientes de una agencia matrimonial para que tome
// los datos de todos los candidatos a estudiar

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct P {
    char n[31];
    int e;
    char s;
    char f[11];
};

void wr(ofstream &f, P &p) {
    f.write(reinterpret_cast<const char*>(&p), sizeof(p));
}

void imp(const P &p) {
    cout << "Nombre: " << p.n << endl;
    cout << "Edad: " << p.e << endl;
    cout << "Sexo: " << p.s << endl;
    cout << "Fecha de Nacimiento: " << p.f << endl;
    cout << "------------------------" << endl;
}

bool can(const P &candidate, const P &client) {
    return (candidate.s != client.s) && (strncmp(candidate.f + 3, client.f + 3, 7) == 0);
}

int main() {
    ifstream f("PERSONAS.DAT", ios::binary);

    if (!f.is_open()) {
        cerr << "Error al abrir el archivo PERSONAS.DAT" << endl;
        return 1;
    }

    ofstream af("ACEPTADOS.DAT", ios::binary);

    if (!af.is_open()) {
        cerr << "Error al abrir el archivo ACEPTADOS.DAT" << endl;
        return 1;
    }

    P c;
    cout << "Ingrese sus datos:" << endl;
    cout << "Nombre: ";
    cin.getline(c.n, sizeof(c.n));

    cout << "Edad: ";
    cin >> c.e;

    cout << "Sexo (M/F): ";
    cin >> c.s;
    c.s = toupper(c.s);

    cout << "Fecha de Nacimiento (dd/mm/yyyy): ";
    cin >> c.f;

    cout << "Candidatos aceptados:" << endl;

    while (true) {
        P p;
        f.read(reinterpret_cast<char*>(&p), sizeof(p));

        if (f.eof()) {
            break;
        }

        if (can(p, c)) {
            // Candidato aceptado, imprimir información y escribir en ACEPTADOS.DAT
            imp(p);
            wr(af, p);
        }
    }

    f.close();
    af.close();

    cout << "Proceso finalizado. Se ha creado el archivo ACEPTADOS.DAT con los candidatos aceptados." << endl;

    return 0;
}

