// Materia: Programación I, Paralelo 2

// Autor: Raquel Osorio Mamani

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023
 
// Número de ejericio: 7

// Problema planteado: Escriba un programa que tenga como entrada un fichero que contenga un texto y dé como
// resultado una estadística del número de palabras.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool saveToFile(const string& filename, const string& content) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return false;
    }

    file << content;
    file.close();

    cout << "Texto guardado en el archivo " << filename << "." << endl;

    return true;
}

int countWords(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return -1;
    }

    string word;
    int wordCount = 0;

    while (file >> word) {
        if (!word.empty()) {
            wordCount++;
        }
    }

    file.close();
    return wordCount;
}

int main() {
    string userInput;
    cout << "Ingrese un texto: ";
    getline(cin, userInput);

    string filename;
    cout << "Ingrese el nombre del archivo para guardar el texto: ";
    cin >> filename;

    if (!saveToFile(filename, userInput)) {
        return 1;
    }

    // Lee el archivo y cuenta las palabras.
    int wordCount = countWords(filename);

    if (wordCount >= 0) {
        cout << "Número de palabras en el archivo " << filename << ": " << wordCount << endl;
    }

    return 0;
}
