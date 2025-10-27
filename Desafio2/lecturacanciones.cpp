#include "lecturaCanciones.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "eficiencia.h"

LecturaCanciones::LecturaCanciones() {
    MedidorEficiencia::incrementarIteraciones();
    listaCanciones = nullptr;
    totalCanciones = 0;
    MedidorEficiencia::sumarMemoria(sizeof(listaCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(totalCanciones));
}


LecturaCanciones::~LecturaCanciones() {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::restarMemoria(totalCanciones * sizeof(Cancion));
    delete[] listaCanciones;
}

void LecturaCanciones::cargarCanciones(string nombreArchivo) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombreArchivo) + nombreArchivo.capacity());

    ifstream archivo(nombreArchivo);
    MedidorEficiencia::sumarMemoria(sizeof(archivo));
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    MedidorEficiencia::sumarMemoria(sizeof(linea));
    totalCanciones = 0;

    while (getline(archivo, linea)) {
        MedidorEficiencia::incrementarIteraciones();
        if (!linea.empty()) {
            totalCanciones++;
        }
    }
    MedidorEficiencia::sumarMemoria(linea.capacity());

    if (totalCanciones == 0) {
        cout << "No hay canciones en el archivo." << endl;
        archivo.close();
        return;
    }

    MedidorEficiencia::restarMemoria(totalCanciones * sizeof(Cancion));
    delete[] listaCanciones;
    listaCanciones = new Cancion[totalCanciones];
    MedidorEficiencia::sumarMemoria(sizeof(listaCanciones));
    MedidorEficiencia::sumarMemoria(totalCanciones * sizeof(Cancion));

    archivo.clear();
    archivo.seekg(0);

    int i = 0;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    while (getline(archivo, linea) && i < totalCanciones) {
        MedidorEficiencia::incrementarIteraciones();
        if (linea.empty()) continue;

        try {
            MedidorEficiencia::incrementarIteraciones();
            int pos1 = linea.find(';');
            MedidorEficiencia::sumarMemoria(sizeof(pos1));
            int pos2 = linea.find(';', pos1 + 1);
            MedidorEficiencia::sumarMemoria(sizeof(pos2));
            int pos3 = linea.find(';', pos2 + 1);
            MedidorEficiencia::sumarMemoria(sizeof(pos3));
            int pos4 = linea.find(';', pos3 + 1);
            MedidorEficiencia::sumarMemoria(sizeof(pos4));

            if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos) {
                continue;
            }

            long id = stoll(linea.substr(0, pos1));
            MedidorEficiencia::sumarMemoria(sizeof(id));
            string nom = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            MedidorEficiencia::sumarMemoria(sizeof(nom) + nom.capacity());
            string dur = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            MedidorEficiencia::sumarMemoria(sizeof(dur) + dur.capacity());
            string r128 = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            MedidorEficiencia::sumarMemoria(sizeof(r128) + r128.capacity());
            string r320 = linea.substr(pos4 + 1);
            MedidorEficiencia::sumarMemoria(sizeof(r320) + r320.capacity());

            listaCanciones[i].setDatos(id, nom, dur, r128, r320);
            i++;

        } catch (...) {
            MedidorEficiencia::incrementarIteraciones();
            cout << "Error al parsear linea de cancion: " << linea << endl;
        }
    }
    MedidorEficiencia::sumarMemoria(linea.capacity());
    archivo.close();
}

Cancion* LecturaCanciones::buscarCancionPorID(long idBuscado) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(idBuscado));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < totalCanciones; i++) {
        MedidorEficiencia::incrementarIteraciones();
        if (listaCanciones[i].obtenerID() == idBuscado) {
            return &listaCanciones[i];
        }
    }
    cout << "Cancion con ID " << idBuscado << " no encontrada en memoria." << endl;
    return nullptr;
}

Cancion* LecturaCanciones::obtenerCancionAleatoria() {
    MedidorEficiencia::incrementarIteraciones();
    if (totalCanciones == 0) {
        return nullptr;
    }

    int indiceAleatorio = rand() % totalCanciones;
    MedidorEficiencia::sumarMemoria(sizeof(indiceAleatorio));

    return &listaCanciones[indiceAleatorio];
}
