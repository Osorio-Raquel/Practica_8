// Materia: Programación I, Paralelo 2

// Autor: Raquel Osorio Mamani

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023
 
// Número de ejericio: 1

// Problema planteado: Escribir un programa con la opción de encriptar y de desencriptar un fichero de texto.

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
const char* NOMBRE_ARCHIVO = "Personas.COD";

void encriptar(){
    string dato;
    int large;
    cout << "Ingrese el dato a encriptar: ";
    cin.ignore();
    getline(cin,dato);
    large = dato.length();
    char data[large];
    for (int i = 0; i<large; i++){
        data[i] = dato[i] + 3;
    }
    cout << "el dato encriptado guardado es: " << data;
    ofstream archivoEscritura;
    archivoEscritura.open(NOMBRE_ARCHIVO);
    archivoEscritura << data;
    archivoEscritura.close();
}
void desencriptar(){
    string dato;
    ifstream archivoEscritura;
    archivoEscritura.open(NOMBRE_ARCHIVO);
    getline(archivoEscritura,dato);
    int large;
    large = dato.length();
    char data[large];
    for (int i = 0; i<large; i++){
        data[i] = dato[i] - 3;
    }
    archivoEscritura.close();
    cout << data;
}

int main() {
    int o;

    do {
        cout << "\nMenú:\n";
        cout << "1. Encriptar\n";
        cout << "2. Desencriptar\n";
        cout << "3. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> o;

        switch (o) {
            case 1:
                encriptar();
                break;

            case 2:
                desencriptar();
                break;

            case 3:
                cout << "Saliendo del programa. Hasta luego.\n";
                break;

            default:
                cout << "Opcion no valida\n";
                break;
        }

    } while (o != 3);

    return 0;
}
