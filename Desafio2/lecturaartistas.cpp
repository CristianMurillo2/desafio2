#include "lecturaartistas.h"
#include <iostream>
#include <fstream>
#include <string>
#include "eficiencia.h"

LecturaArtistas::LecturaArtistas() {
    MedidorEficiencia::incrementarIteraciones();
    listaArtistas = nullptr;
    totalArtistas = 0;
    MedidorEficiencia::sumarMemoria(sizeof(listaArtistas));
    MedidorEficiencia::sumarMemoria(sizeof(totalArtistas));
}

LecturaArtistas::~LecturaArtistas() {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::restarMemoria(totalArtistas * sizeof(Artista));
    delete[] listaArtistas;
}

void LecturaArtistas::cargarArtistas(string nombreArchivo) {
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
    totalArtistas = 0;

    while (getline(archivo, linea)) {
        MedidorEficiencia::incrementarIteraciones();
        if (!linea.empty()) {
            totalArtistas++;
        }
    }
    MedidorEficiencia::sumarMemoria(linea.capacity());

    if (totalArtistas == 0) {
        cout << "No hay artistas en el archivo." << endl;
        archivo.close();
        return;
    }

    MedidorEficiencia::restarMemoria(totalArtistas * sizeof(Artista));
    delete[] listaArtistas;
    listaArtistas = new Artista[totalArtistas];
    MedidorEficiencia::sumarMemoria(sizeof(listaArtistas));
    MedidorEficiencia::sumarMemoria(totalArtistas * sizeof(Artista));

    archivo.clear();
    archivo.seekg(0);

    int i = 0;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    while (getline(archivo, linea) && i < totalArtistas) {
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
            int pos5 = linea.find(';', pos4 + 1);
            MedidorEficiencia::sumarMemoria(sizeof(pos5));

            if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos || pos5 == string::npos) {
                continue;
            }

            long id = stoll(linea.substr(0, pos1));
            MedidorEficiencia::sumarMemoria(sizeof(id));
            string nom = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            MedidorEficiencia::sumarMemoria(sizeof(nom) + nom.capacity());
            string p = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            MedidorEficiencia::sumarMemoria(sizeof(p) + p.capacity());
            int ed = stoi(linea.substr(pos3 + 1, pos4 - pos3 - 1));
            MedidorEficiencia::sumarMemoria(sizeof(ed));
            int seg = stoi(linea.substr(pos4 + 1, pos5 - pos4 - 1));
            MedidorEficiencia::sumarMemoria(sizeof(seg));
            int pos = stoi(linea.substr(pos5 + 1));
            MedidorEficiencia::sumarMemoria(sizeof(pos));

            listaArtistas[i].setDatos(id, nom, p, ed, seg, pos);
            i++;

        } catch (...) {
            MedidorEficiencia::incrementarIteraciones();
            cout << "Error al copiar la linea de artista: " << linea << endl;
        }
    }
    MedidorEficiencia::sumarMemoria(linea.capacity());
    archivo.close();
}

Artista* LecturaArtistas::buscarArtistaPorID(long idBuscado) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(idBuscado));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < totalArtistas; i++) {
        MedidorEficiencia::incrementarIteraciones();
        if (listaArtistas[i].obtenerID() == idBuscado) {
            return &listaArtistas[i];
        }
    }

    return nullptr;
}
