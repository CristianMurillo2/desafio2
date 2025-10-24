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

Album::Album(long idAlbum, long idArtista, const string& nombre, int capacidad) {
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

string Album::getNombre() const { return nombre; }
void Album::setNombre(const string& n) { nombre = n; }

string Album::getFechaLanzamiento() const { return fechaLanzamiento; }
void Album::setFechaLanzamiento(const string& f) { fechaLanzamiento = f; }

string Album::getSello() const { return sello; }
void Album::setSello(const string& s) { sello = s; }

string Album::getPortada() const { return portada; }
void Album::setPortada(const string& p) { portada = p; }

float Album::getPuntuacion() const { return puntuacion; }
void Album::setPuntuacion(float p) { puntuacion = p; }

string Album::getGenero(int i) const {
    if (i < 0 || i >= 4) return "N/A";
    return generos[i];
}
void Album::setGenero(int i, const string& g) {
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

void Album::guardarEnArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;

    archivo << idAlbum << ";" << nombre << ";" << idArtista << ";"
            << fechaLanzamiento << ";" << sello << ";" << puntuacion << "\n";

    for (int i = 0; i < numCanciones; i++)
        archivo << cancionesIDs[i] << "\n";

    archivo.close();
}

Album* Album::cargarAlbumes(string nombreArchivo, int& totalAlbumes) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        totalAlbumes = 0;
        return nullptr;
    }
    string linea;
    totalAlbumes = 0;
    while (getline(archivo, linea)) {
        if (!linea.empty()) { // Ignora líneas vacías
            totalAlbumes++;
        }
    }
    if (totalAlbumes == 0) {
        archivo.close();
        return nullptr;
    }
    Album* listaAlbumes = new Album[totalAlbumes];
    archivo.clear();
    archivo.seekg(0);
    int i = 0;
    while (getline(archivo, linea) && i < totalAlbumes) {
        if (linea.empty()) continue;
        try {
            size_t pos1 = linea.find(';');
            if (pos1 == string::npos) continue;
            string idArtistaStr = linea.substr(0, pos1);
            size_t pos2 = linea.find(';', pos1 + 1);
            if (pos2 == string::npos) continue;
            string idAlbumStr = linea.substr(pos1 + 1, pos2 - (pos1 + 1));
            size_t pos3 = linea.find(';', pos2 + 1);
            if (pos3 == string::npos) continue;
            string nombre = linea.substr(pos2 + 1, pos3 - (pos2 + 1));
            string rutaPortada = linea.substr(pos3 + 1);
            listaAlbumes[i].setIdArtista(stoll(idArtistaStr));
            listaAlbumes[i].setIdAlbum(stoll(idAlbumStr));
            listaAlbumes[i].setNombre(nombre);
            listaAlbumes[i].setPortada(rutaPortada);
            i++;
        } catch (const invalid_argument& e) {
            cout << "Error de formato numerico en linea de album: " << linea << " (" << e.what() << ")" << endl;
        } catch (const out_of_range& e) {
            cout << "Error de rango numerico en linea de album: " << linea << " (" << e.what() << ")" << endl;
        } catch (...) {
            cout << "Error desconocido al parsear linea de album: " << linea << endl;
        }
    }
    archivo.close();
    totalAlbumes = i;
    return listaAlbumes;
}

Album* Album::buscarAlbumPorIDs(Album* listaAlbumes, int totalAlbumes, long idArtista, long idAlbumNum) {
    if (listaAlbumes == nullptr) return nullptr;

    for (int i = 0; i < totalAlbumes; i++) {
        if (listaAlbumes[i].getIdArtista() == idArtista && listaAlbumes[i].getIdAlbum() == idAlbumNum) {
            return &listaAlbumes[i];
        }
    }
    return nullptr;
}


