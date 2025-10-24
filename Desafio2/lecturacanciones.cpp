#include "lecturaCanciones.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


LecturaCanciones::LecturaCanciones() {
    listaCanciones = nullptr;
    totalCanciones = 0;
}


LecturaCanciones::~LecturaCanciones() {
    delete[] listaCanciones;
}

void LecturaCanciones::cargarCanciones(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    totalCanciones = 0;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            totalCanciones++;
        }
    }

    if (totalCanciones == 0) {
        cout << "No hay canciones en el archivo." << endl;
        archivo.close();
        return;
    }

    delete[] listaCanciones;
    listaCanciones = new Cancion[totalCanciones];

    archivo.clear();
    archivo.seekg(0);

    int i = 0;
    while (getline(archivo, linea) && i < totalCanciones) {
        if (linea.empty()) continue;

        try {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);
            int pos4 = linea.find(';', pos3 + 1);

            if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos) {
                continue; // Línea mal formateada
            }

            long id = stoll(linea.substr(0, pos1));
            string nom = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string dur = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            string r128 = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            string r320 = linea.substr(pos4 + 1);

            listaCanciones[i].setDatos(id, nom, dur, r128, r320);
            i++;

        } catch (...) {
            cout << "Error al parsear linea de cancion: " << linea << endl;
        }
    }

    archivo.close();
}

Cancion* LecturaCanciones::buscarCancionPorID(long idBuscado) {
    for (int i = 0; i < totalCanciones; i++) {
        if (listaCanciones[i].obtenerID() == idBuscado) {
            return &listaCanciones[i];
        }
    }
    cout << "Cancion con ID " << idBuscado << " no encontrada en memoria." << endl;
    return nullptr;
}

Cancion* LecturaCanciones::obtenerCancionAleatoria() {
    if (totalCanciones == 0) {
        return nullptr;
    }


    int indiceAleatorio = rand() % totalCanciones;

    return &listaCanciones[indiceAleatorio];
}
