#include "playlist.h"
#include <iostream>
#include <fstream>
#include "lecturacanciones.h"

using namespace std;

Playlist::Playlist() {
    nombre = "Favoritos";
    maxCanciones = 20;
    numCanciones = 0;
    indiceActual = 0;
    cancionesIDs = new long[maxCanciones];
    posHistorial = 0;
    cancionesEnHistorial = 0;
}

Playlist::Playlist(const std::string& nombre, int capacidadMax) {
    this->nombre = nombre;
    maxCanciones = capacidadMax > 0 ? capacidadMax : 20;
    numCanciones = 0;
    indiceActual = 0;
    cancionesIDs = new long[maxCanciones];
    posHistorial = 0;
    cancionesEnHistorial = 0;
}

Playlist::Playlist(const Playlist& otra) {
    nombre = otra.nombre;
    maxCanciones = otra.maxCanciones;
    numCanciones = otra.numCanciones;
    indiceActual = otra.indiceActual;
    posHistorial = otra.posHistorial;
    cancionesEnHistorial = otra.cancionesEnHistorial;

    cancionesIDs = new long[maxCanciones];
    for (int i = 0; i < numCanciones; i++)
        cancionesIDs[i] = otra.cancionesIDs[i];

    for (int i = 0; i < 6; i++)
        historial[i] = otra.historial[i];
}

Playlist::~Playlist() {
    delete[] cancionesIDs;
}

Playlist& Playlist::operator=(const Playlist& otra) {
    if (this != &otra) {
        delete[] cancionesIDs;

        nombre = otra.nombre;
        maxCanciones = otra.maxCanciones;
        numCanciones = otra.numCanciones;
        indiceActual = otra.indiceActual;
        posHistorial = otra.posHistorial;
        cancionesEnHistorial = otra.cancionesEnHistorial;

        cancionesIDs = new long[maxCanciones];
        for (int i = 0; i < numCanciones; i++)
            cancionesIDs[i] = otra.cancionesIDs[i];

        for (int i = 0; i < 6; i++)
            historial[i] = otra.historial[i];
    }
    return *this;
}

std::string Playlist::getNombre() const { return nombre; }
void Playlist::setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }
int Playlist::getNumCanciones() const { return numCanciones; }
int Playlist::getMaxCanciones() const { return maxCanciones; }
int Playlist::getIndiceActual() const { return indiceActual; }
void Playlist::setIndiceActual(int indice) { if (indice >= 0 && indice < numCanciones) indiceActual = indice; }
long Playlist::getCancionID(int indice) const { if (indice >= 0 && indice < numCanciones) return cancionesIDs[indice]; return 0; }
void Playlist::setCancionID(int indice, long id) { if (indice >= 0 && indice < numCanciones) cancionesIDs[indice] = id; }


bool Playlist::agregarCancion(long idCancion) {
    for (int i = 0; i < numCanciones; i++) {
        if (cancionesIDs[i] == idCancion) {
            return false;
        }
    }

    if (numCanciones >= maxCanciones) {
        return false;
    }

    cancionesIDs[numCanciones] = idCancion;
    numCanciones++;
    return true;
}

bool Playlist::eliminarCancion(long idCancion) {
    int indice = -1;
    for (int i = 0; i < numCanciones; i++) {
        if (cancionesIDs[i] == idCancion) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        return false;
    }
    for (int i = indice; i < numCanciones - 1; i++) {
        cancionesIDs[i] = cancionesIDs[i + 1];
    }
    numCanciones--;
    return true;
}

void Playlist::mostrar(int esPremium) const {
    cout << "Playlist: " << nombre << endl;
    if (numCanciones == 0) {
        cout << "(Vacia)" << endl;
        return;
    }
    for (int i = 0; i < numCanciones; i++) {
        cout << "  " << i + 1 << ". ID: " << cancionesIDs[i] << endl;
    }
}

Cancion Playlist::_reproducirIndiceActual(int esPremium, LecturaCanciones& gestor) {
    if (numCanciones == 0) return Cancion();

    long idActual = cancionesIDs[indiceActual];
    Cancion* cancionPtr = gestor.buscarCancionPorID(idActual);

    if (cancionPtr != nullptr) {
        return *cancionPtr;
    } else {
        return Cancion();
    }
}

Cancion Playlist::reproducirActual(int esPremium, LecturaCanciones& gestor) {
    if (numCanciones == 0) return Cancion();

    return _reproducirIndiceActual(esPremium, gestor);
}

Cancion Playlist::siguiente(int esPremium, LecturaCanciones& gestor) {
    if (numCanciones == 0) return Cancion();

    historial[posHistorial] = indiceActual;
    posHistorial = (posHistorial + 1) % 6;

    if (cancionesEnHistorial < 6) {
        cancionesEnHistorial++;
    }

    indiceActual = (indiceActual + 1) % numCanciones;

    return _reproducirIndiceActual(esPremium, gestor);
}

Cancion Playlist::anterior(int esPremium, LecturaCanciones& gestor) {

    if (esPremium == 0) {
        return _reproducirIndiceActual(esPremium, gestor);
    }

    if (cancionesEnHistorial == 0) {
        return _reproducirIndiceActual(esPremium, gestor);
    }

    posHistorial = (posHistorial - 1 + 6) % 6;
    indiceActual = historial[posHistorial];
    cancionesEnHistorial--;

    return _reproducirIndiceActual(esPremium, gestor);
}

void Playlist::guardarEnArchivo(const std::string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;

    archivo << nombre << '\n';
    for (int i = 0; i < numCanciones; i++)
        archivo << cancionesIDs[i] << '\n';

    archivo.close();
}

Playlist Playlist::cargarDesdeArchivo(const std::string& nombreArchivo, int capacidadMax) {
    Playlist pl("Cargada", capacidadMax);
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return pl;
    }

    getline(archivo, pl.nombre);

    long id;
    while (archivo >> id) {
        pl.agregarCancion(id);
    }

    archivo.close();
    return pl;
}
