// Materia: Programación I, Paralelo 2

// Autor: Raquel Osorio Mamani

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023
 
// Número de ejericio: 2

// Problema planteado: Escriba un programa que cree un fichero de texto llamado "PERSONAS.BIN" en el que se
// guarde la información de un número indeterminado de personas.

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

struct P {
    char n[31];
    int e;
    char s;
    char f[11];
};

void wr(ofstream& f, P& p) {
    f.write(reinterpret_cast<const char*>(&p), sizeof(p));
}

void displayData(const P& p) {
    cout << "Nombre: " << p.n << endl;
    cout << "Edad: " << p.e << endl;
    cout << "Género: " << p.s << endl;
    cout << "Fecha de nacimiento: " << p.f << endl
         << endl;
}

bool validateAge(const P& p) {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    int currentYear = now->tm_year + 1900;

    int birthYear = stoi(p.f + 6);

    return (currentYear - birthYear) == p.e;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool validateDate(const P& p) {
    int day, month, year;
    sscanf(p.f, "%d/%d/%d", &day, &month, &year);

    if (month < 1 || month > 12) {
        cout << "Error: Mes no válido." << endl;
        return false;
    }

    int daysInMonth;

    switch (month) {
        case 2:
            daysInMonth = isLeapYear(year) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            daysInMonth = 30;
            break;
        default:
            daysInMonth = 31;
            break;
    }

    if (day < 1 || day > daysInMonth) {
        cout << "Error: Día no válido para el mes ingresado." << endl;
        return false;
    }

    return true;
}

int main() {
    ofstream f("PERSONAS.DAT", ios::app | ios::binary);

    if (!f.is_open()) {
        cerr << "Error al abrir el archivo PERSONAS.DAT" << endl;
        return 1;
    }

    do {
        P p;

        cout << "Ingrese su nombre (espacio para salir): ";
        cin.getline(p.n, sizeof(p.n));

        if (p.n[0] == ' ' || p.n[0] == '\0') {
            break;
        }

        do {
            cout << "Ingresa la edad (1-100): ";
            cin >> p.e;
            while (p.e < 1 || p.e > 100) {
                cout << "Edad fuera del rango permitido. Ingrese nuevamente: ";
                cin >> p.e;
            }

            cout << "Ingrese el género (M/F): ";
            cin >> p.s;
            p.s = toupper(p.s);
            while (p.s != 'M' && p.s != 'F') {
                cout << "Sexo no válido ingrese (M/F): ";
                cin >> p.s;
                p.s = toupper(p.s);
            }

            cout << "Ingrese la fecha de nacimiento (dd/mm/yyyy): ";
            cin >> p.f;

            if (!validateAge(p) || !validateDate(p)) {
                cout << "Error en la validación. Vuelva a ingresar los datos." << endl;
            }

        } while (!validateAge(p) || !validateDate(p));

        wr(f, p);

        cin.ignore();

    } while (true);

    f.close();

    ifstream readF("PERSONAS.DAT", ios::binary);

    if (!readF.is_open()) {
        cerr << "Error al abrir el archivo PERSONAS.DAT para lectura." << endl;
        return 1;
    }

    P person;
    cout << "\nDatos guardados:\n";
    while (readF.read(reinterpret_cast<char*>(&person), sizeof(person))) {
        displayData(person);
    }

    readF.close();

    return 0;
}


