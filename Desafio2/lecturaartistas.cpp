#include "lecturaartistas.h"
#include <iostream>
#include <fstream>
#include <string>
LecturaArtistas::LecturaArtistas() {
    listaArtistas = nullptr;
    totalArtistas = 0;
}

LecturaArtistas::~LecturaArtistas() {
    delete[] listaArtistas;
}

void LecturaArtistas::cargarArtistas(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    totalArtistas = 0;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            totalArtistas++;
        }
    }

    if (totalArtistas == 0) {
        cout << "No hay artistas en el archivo." << endl;
        archivo.close();
        return;
    }

    delete[] listaArtistas;
    listaArtistas = new Artista[totalArtistas];

    archivo.clear();
    archivo.seekg(0);

    int i = 0;
    while (getline(archivo, linea) && i < totalArtistas) {
        if (linea.empty()) continue;

        try {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);
            int pos4 = linea.find(';', pos3 + 1);
            int pos5 = linea.find(';', pos4 + 1);

            if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos || pos5 == string::npos) {
                continue;
            }

            long id = stoll(linea.substr(0, pos1));
            string nom = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string p = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            int ed = stoi(linea.substr(pos3 + 1, pos4 - pos3 - 1));
            int seg = stoi(linea.substr(pos4 + 1, pos5 - pos4 - 1));
            int pos = stoi(linea.substr(pos5 + 1));

            listaArtistas[i].setDatos(id, nom, p, ed, seg, pos);
            i++;

        } catch (...) {
            cout << "Error al copiar la linea de artista: " << linea << endl;
        }
    }

    archivo.close();
}

Artista* LecturaArtistas::buscarArtistaPorID(long idBuscado) {
    for (int i = 0; i < totalArtistas; i++) {
        if (listaArtistas[i].obtenerID() == idBuscado) {
            return &listaArtistas[i];
        }
    }

    return nullptr;
}
