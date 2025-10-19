#include "Playlist.h"
#include <iostream>

Playlist::Playlist() {
    nombre = "Sin nombre";
    maxCanciones = 10000;
    numCanciones = 0;
    indiceActual = -1;
    canciones = new Cancion*[maxCanciones];
}
Playlist::Playlist(const std::string& nombre, int capacidadMax) {
    this->nombre = nombre;
    this->maxCanciones = capacidadMax;
    this->numCanciones = 0;
    this->indiceActual = -1;
    this->canciones = new Cancion*[maxCanciones];
    for (int i = 0; i < 4; i++) historial[i] = -1;
    posHistorial = 0;
    cancionesEnHistorial = 0;
}

Playlist::Playlist(const Playlist& otra) {
    nombre = otra.nombre;
    maxCanciones = otra.maxCanciones;
    numCanciones = otra.numCanciones;
    indiceActual = otra.indiceActual;
    canciones = new Cancion*[maxCanciones];
    for (int i = 0; i < numCanciones; i++) {
        canciones[i] = otra.canciones[i];
    }
}

Playlist::~Playlist() {
    delete[] canciones;
    canciones = nullptr;
}
Playlist& Playlist::operator=(const Playlist& otra) {
    if (this != &otra) {
        delete[] canciones;

        nombre = otra.nombre;
        maxCanciones = otra.maxCanciones;
        numCanciones = otra.numCanciones;
        indiceActual = otra.indiceActual;

        canciones = new Cancion*[maxCanciones];
        for (int i = 0; i < numCanciones; i++) {
            canciones[i] = otra.canciones[i];
        }
    }
    return *this;
}

std::string Playlist::getNombre() const {
    return nombre;
}

void Playlist::setNombre(const std::string& nuevoNombre) {
    nombre = nuevoNombre;
}

int Playlist::getNumCanciones() const {
    return numCanciones;
}

int Playlist::getMaxCanciones() const {
    return maxCanciones;
}

int Playlist::getIndiceActual() const {
    return indiceActual;
}

bool Playlist::agregarCancion(Cancion* c) {
    if (numCanciones >= maxCanciones) return false;
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i]->getIdCancion() == c->getIdCancion()) {
            return false;
        }
    }

    canciones[numCanciones++] = c;
    if (indiceActual == -1) indiceActual = 0;
    return true;
}

bool Playlist::eliminarCancion(int idCancion) {
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i]->getIdCancion() == idCancion) {
            for (int j = i; j < numCanciones - 1; j++) {
                canciones[j] = canciones[j + 1];
            }
            numCanciones--;
            if (indiceActual >= numCanciones) indiceActual = numCanciones - 1;
            return true;
        }
    }
    return false;
}

void Playlist::mostrar() const {
    std::cout << "Playlist: " << nombre << " (" << numCanciones << " canciones)\n";
    for (int i = 0; i < numCanciones; i++) {
        std::cout << "  - ";
        canciones[i]->mostrarInfo();
    }
}

Cancion* Playlist::siguiente() {
    if (numCanciones == 0) return nullptr;
    if (indiceActual != -1) {
        historial[posHistorial] = indiceActual;
        posHistorial = (posHistorial + 1) % 4;
        if (cancionesEnHistorial < 4) cancionesEnHistorial++;
    }

    indiceActual = (indiceActual + 1) % numCanciones;
    return canciones[indiceActual];
}
Cancion* Playlist::anterior() {
    if (cancionesEnHistorial == 0) {
        std::cout << "No hay canciones previas disponibles.\n";
        return nullptr;
    }

    posHistorial = (posHistorial - 1 + 4) % 4;
    int indicePrevio = historial[posHistorial];

    if (indicePrevio == -1) {
        std::cout << " No hay más canciones anteriores (máximo 4 permitidas).\n";
        return nullptr;
    }

    indiceActual = indicePrevio;
    cancionesEnHistorial--;
    return canciones[indiceActual];
}
