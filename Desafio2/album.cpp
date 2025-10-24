#include "album.h"
#include <iostream>
#include <fstream>
#include "cancion.h"
using namespace std;

Album::Album() {
    idAlbum = 0;
    idArtista = 0;
    nombre = "Sin nombre";
    fechaLanzamiento = "Desconocida";
    sello = "Independiente";
    portada = "N/A";
    puntuacion = 0.0f;
    numCanciones = 0;
    maxCanciones = 20;
    cancionesIDs = new long[maxCanciones];
    for (int i = 0; i < 4; i++)
        generos[i] = "N/A";
}

Album::Album(long idAlbum, long idArtista, const std::string& nombre, int capacidad) {
    this->idAlbum = idAlbum;
    this->idArtista = idArtista;
    this->nombre = nombre;
    fechaLanzamiento = "Desconocida";
    sello = "Independiente";
    portada = "N/A";
    puntuacion = 0.0f;
    numCanciones = 0;
    maxCanciones = capacidad > 0 ? capacidad : 20;
    cancionesIDs = new long[maxCanciones];
    for (int i = 0; i < 4; i++)
        generos[i] = "N/A";
}

Album::Album(const Album& otro) {
    idAlbum = otro.idAlbum;
    idArtista = otro.idArtista;
    nombre = otro.nombre;
    fechaLanzamiento = otro.fechaLanzamiento;
    sello = otro.sello;
    portada = otro.portada;
    puntuacion = otro.puntuacion;
    numCanciones = otro.numCanciones;
    maxCanciones = otro.maxCanciones;

    cancionesIDs = new long[maxCanciones];
    for (int i = 0; i < numCanciones; i++)
        cancionesIDs[i] = otro.cancionesIDs[i];
    for (int i = 0; i < 4; i++)
        generos[i] = otro.generos[i];
}

Album::~Album() {
    delete[] cancionesIDs;
}

Album& Album::operator=(const Album& otro) {
    if (this != &otro) {
        delete[] cancionesIDs;

        idAlbum = otro.idAlbum;
        idArtista = otro.idArtista;
        nombre = otro.nombre;
        fechaLanzamiento = otro.fechaLanzamiento;
        sello = otro.sello;
        portada = otro.portada;
        puntuacion = otro.puntuacion;
        numCanciones = otro.numCanciones;
        maxCanciones = otro.maxCanciones;

        cancionesIDs = new long[maxCanciones];
        for (int i = 0; i < numCanciones; i++)
            cancionesIDs[i] = otro.cancionesIDs[i];
        for (int i = 0; i < 4; i++)
            generos[i] = otro.generos[i];
    }
    return *this;
}

long Album::getIdAlbum() const { return idAlbum; }
void Album::setIdAlbum(long id) { idAlbum = id; }

long Album::getIdArtista() const { return idArtista; }
void Album::setIdArtista(long id) { idArtista = id; }

std::string Album::getNombre() const { return nombre; }
void Album::setNombre(const std::string& n) { nombre = n; }

std::string Album::getFechaLanzamiento() const { return fechaLanzamiento; }
void Album::setFechaLanzamiento(const std::string& f) { fechaLanzamiento = f; }

std::string Album::getSello() const { return sello; }
void Album::setSello(const std::string& s) { sello = s; }

std::string Album::getPortada() const { return portada; }
void Album::setPortada(const std::string& p) { portada = p; }

float Album::getPuntuacion() const { return puntuacion; }
void Album::setPuntuacion(float p) { puntuacion = p; }

std::string Album::getGenero(int i) const {
    if (i < 0 || i >= 4) return "N/A";
    return generos[i];
}
void Album::setGenero(int i, const std::string& g) {
    if (i >= 0 && i < 4) generos[i] = g;
}

int Album::getNumCanciones() const { return numCanciones; }
int Album::getMaxCanciones() const { return maxCanciones; }

long Album::getCancionID(int i) const {
    if (i < 0 || i >= numCanciones) return -1;
    return cancionesIDs[i];
}
void Album::setCancionID(int i, long id) {
    if (i >= 0 && i < maxCanciones)
        cancionesIDs[i] = id;
}

bool Album::agregarCancion(long idCancion) {
    if (numCanciones >= maxCanciones) return false;
    cancionesIDs[numCanciones++] = idCancion;
    return true;
}

bool Album::eliminarCancion(long idCancion) {
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

void Album::mostrar(int esPremium) const {
    cout << "\nÁlbum: " << nombre << " (" << numCanciones << " canciones)\n";
    for (int i = 0; i < numCanciones; i++) {
        Cancion c;
        c.setDatos(cancionesIDs[i], "Desconocida", "0", "ruta128.mp3", "ruta320.mp3");
        cout << "- " << c.obtenerNombre()
             << " | Duración: " << c.obtenerDuracion()
             << " | Ruta: " << c.obtenerRutaAudio(esPremium) << "\n";
    }
}

float Album::calcularDuracionTotal(int esPremium) const {
    float total = 0;
    for (int i = 0; i < numCanciones; i++) {
        Cancion c;
        c.setDatos(cancionesIDs[i], "Desconocida", "0", "ruta128.mp3", "ruta320.mp3");
        try {
            total += stof(c.obtenerDuracion());
        } catch (...) {}
    }
    return total;
}

void Album::guardarEnArchivo(const std::string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;

    archivo << idAlbum << ";" << nombre << ";" << idArtista << ";"
            << fechaLanzamiento << ";" << sello << ";" << puntuacion << "\n";

    for (int i = 0; i < numCanciones; i++)
        archivo << cancionesIDs[i] << "\n";

    archivo.close();
}

Album Album::cargarDesdeArchivo(const std::string& nombreArchivo, int capacidad) {
    Album al(0, 0, "Cargado", capacidad);
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return al;

    string linea;
    getline(archivo, linea); // primera línea con datos generales
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        try {
            long id = stol(linea);
            al.agregarCancion(id);
        } catch (...) {}
    }

    archivo.close();
    return al;
}
