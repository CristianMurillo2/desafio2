#include "playlist.h"
#include <iostream>
#include <fstream>
using namespace std;

// --- Constructores ---
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

    cancionesIDs = new long[maxCanciones];
    for (int i = 0; i < numCanciones; i++)
        cancionesIDs[i] = otra.cancionesIDs[i];

    for (int i = 0; i < 4; i++)
        historial[i] = otra.historial[i];

    posHistorial = otra.posHistorial;
    cancionesEnHistorial = otra.cancionesEnHistorial;
}

Playlist::~Playlist() {
    delete[] cancionesIDs;
}

// --- Sobrecarga de operador ---
Playlist& Playlist::operator=(const Playlist& otra) {
    if (this != &otra) {
        delete[] cancionesIDs;

        nombre = otra.nombre;
        maxCanciones = otra.maxCanciones;
        numCanciones = otra.numCanciones;
        indiceActual = otra.indiceActual;

        cancionesIDs = new long[maxCanciones];
        for (int i = 0; i < numCanciones; i++)
            cancionesIDs[i] = otra.cancionesIDs[i];

        for (int i = 0; i < 4; i++)
            historial[i] = otra.historial[i];

        posHistorial = otra.posHistorial;
        cancionesEnHistorial = otra.cancionesEnHistorial;
    }
    return *this;
}

// --- Getters / Setters ---
std::string Playlist::getNombre() const { return nombre; }
void Playlist::setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }

int Playlist::getNumCanciones() const { return numCanciones; }
int Playlist::getMaxCanciones() const { return maxCanciones; }

int Playlist::getIndiceActual() const { return indiceActual; }
void Playlist::setIndiceActual(int indice) {
    if (indice >= 0 && indice < numCanciones)
        indiceActual = indice;
}

long Playlist::getCancionID(int indice) const {
    if (indice < 0 || indice >= numCanciones) return -1;
    return cancionesIDs[indice];
}

void Playlist::setCancionID(int indice, long id) {
    if (indice >= 0 && indice < maxCanciones)
        cancionesIDs[indice] = id;
}

// --- Funcionalidad principal ---
bool Playlist::agregarCancion(long idCancion) {
    if (numCanciones >= maxCanciones) return false;
    cancionesIDs[numCanciones++] = idCancion;
    return true;
}

bool Playlist::eliminarCancion(long idCancion) {
    for (int i = 0; i < numCanciones; i++) {
        if (cancionesIDs[i] == idCancion) {
            for (int j = i; j < numCanciones - 1; j++)
                cancionesIDs[j] = cancionesIDs[j + 1];
            numCanciones--;
            return true;
        }
    }
    return false;
}

// --- Mostrar ---
void Playlist::mostrar(int esPremium) const {
    cout << "\nPlaylist: " << nombre << " (" << numCanciones << " canciones)\n";
    for (int i = 0; i < numCanciones; i++) {
        Cancion c;
        // Simulación de carga desde BD o archivo (solo por ID)
        c.setDatos(cancionesIDs[i], "Desconocida", "0", "ruta128.mp3", "ruta320.mp3");
        cout << "- " << c.obtenerNombre()
             << " | Duración: " << c.obtenerDuracion()
             << " | Ruta: " << c.obtenerRutaAudio(esPremium) << "\n";
    }
}

// --- Reproducción ---
Cancion Playlist::reproducirActual(int esPremium) {
    Cancion c;
    if (numCanciones == 0) return c;

    historial[posHistorial] = indiceActual;
    posHistorial = (posHistorial + 1) % 4;
    if (cancionesEnHistorial < 4) cancionesEnHistorial++;

    c.setDatos(cancionesIDs[indiceActual], "Reproduciendo", "0", "ruta128.mp3", "ruta320.mp3");
    return c;
}

Cancion Playlist::siguiente(int esPremium) {
    if (numCanciones == 0) return Cancion();
    indiceActual = (indiceActual + 1) % numCanciones;
    return reproducirActual(esPremium);
}

Cancion Playlist::anterior(int esPremium) {
    if (numCanciones == 0 || cancionesEnHistorial == 0) return Cancion();
    posHistorial = (posHistorial - 1 + 4) % 4;
    indiceActual = historial[posHistorial];
    cancionesEnHistorial--;
    return reproducirActual(esPremium);
}

// --- Persistencia ---
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
    if (!archivo.is_open()) return pl;

    string linea;
    getline(archivo, linea);
    pl.setNombre(linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        try {
            long id = stol(linea);
            pl.agregarCancion(id);
        } catch (...) {}
    }

    archivo.close();
    return pl;
}
