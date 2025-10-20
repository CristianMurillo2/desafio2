#include "Album.h"
#include <iostream>

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
    canciones = new Cancion*[maxCanciones];
    for (int i = 0; i < 4; i++) generos[i] = "N/A";
}

Album::Album(int idAlbum, int idArtista, const std::string& nombre, int capacidad) {
    this->idAlbum = idAlbum;
    this->idArtista = idArtista;
    this->nombre = nombre;
    fechaLanzamiento = "Desconocida";
    sello = "Independiente";
    portada = "N/A";
    puntuacion = 0.0f;
    numCanciones = 0;
    maxCanciones = capacidad > 0 ? capacidad : 20;
    canciones = new Cancion*[maxCanciones];
    for (int i = 0; i < 4; i++) generos[i] = "N/A";
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

    for (int i = 0; i < 4; i++)
        generos[i] = otro.generos[i];

    canciones = new Cancion*[maxCanciones];
    for (int i = 0; i < numCanciones; i++)
        canciones[i] = otro.canciones[i];
}

Album::~Album() {
    delete[] canciones;
    canciones = nullptr;
}

Album& Album::operator=(const Album& otro) {
    if (this != &otro) {
        delete[] canciones;

        idAlbum = otro.idAlbum;
        idArtista = otro.idArtista;
        nombre = otro.nombre;
        fechaLanzamiento = otro.fechaLanzamiento;
        sello = otro.sello;
        portada = otro.portada;
        puntuacion = otro.puntuacion;
        numCanciones = otro.numCanciones;
        maxCanciones = otro.maxCanciones;

        for (int i = 0; i < 4; i++)
            generos[i] = otro.generos[i];

        canciones = new Cancion*[maxCanciones];
        for (int i = 0; i < numCanciones; i++)
            canciones[i] = otro.canciones[i];
    }
    return *this;
}

int Album::getIdAlbum() const { return idAlbum; }
void Album::setIdAlbum(int id) { idAlbum = id; }

int Album::getIdArtista() const { return idArtista; }
void Album::setIdArtista(int id) { idArtista = id; }

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
    if (i >= 0 && i < 4) return generos[i];
    return "";
}

void Album::setGenero(int i, const std::string& g) {
    if (i >= 0 && i < 4) generos[i] = g;
}

int Album::getNumCanciones() const { return numCanciones; }
bool Album::agregarCancion(Cancion* c) {
    if (numCanciones >= maxCanciones || c == nullptr)
        return false;

    // evitar duplicados
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i]->getIdCancion() == c->getIdCancion())
            return false;
    }

    canciones[numCanciones++] = c;
    return true;
}
Cancion* Album::buscarCancion(int id) const {
    for (int i = 0; i < numCanciones; i++) {
        if (canciones[i]->getIdCancion() == id)
            return canciones[i];
    }
    return nullptr;
}

float Album::calcularDuracionTotal() const {
    float total = 0.0f;
    for (int i = 0; i < numCanciones; i++) {
        total += canciones[i]->getDuracion();
    }
    return total;
}

void Album::mostrarInfo() const {
    std::cout << "Álbum: " << nombre << " (ID: " << idAlbum << ")\n";
    std::cout << "Artista ID: " << idArtista << "\n";
    std::cout << "Fecha: " << fechaLanzamiento << " | Sello: " << sello << "\n";
    std::cout << "Puntuación: " << puntuacion << " | Duración total: "
              << calcularDuracionTotal() << " seg\n";
    std::cout << "Géneros: ";
    for (int i = 0; i < 4; i++) {
        if (generos[i] != "N/A") std::cout << generos[i] << " ";
    }
    std::cout << "\nCanciones (" << numCanciones << "):\n";
    for (int i = 0; i < numCanciones; i++) {
        std::cout << "  - ";
        canciones[i]->mostrarInfo();
    }
    std::cout << "-----------------------------------\n";
}
