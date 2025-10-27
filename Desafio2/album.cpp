#include "album.h"
#include <iostream>
#include <fstream>
#include "cancion.h"
#include "eficiencia.h"
using namespace std;

Album::Album() {
    MedidorEficiencia::incrementarIteraciones();
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

    MedidorEficiencia::sumarMemoria(sizeof(idAlbum));
    MedidorEficiencia::sumarMemoria(sizeof(idArtista));
    MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(fechaLanzamiento) + fechaLanzamiento.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(sello) + sello.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(portada) + portada.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(puntuacion));
    MedidorEficiencia::sumarMemoria(sizeof(numCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(maxCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(cancionesIDs));
    MedidorEficiencia::sumarMemoria(maxCanciones * sizeof(long));
    MedidorEficiencia::sumarMemoria(sizeof(generos));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < 4; i++){
        MedidorEficiencia::incrementarIteraciones();
        generos[i] = "N/A";
    }
}

Album::Album(long idAlbum, long idArtista, const string& nombre, int capacidad) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(idAlbum));
    MedidorEficiencia::sumarMemoria(sizeof(idArtista));
    MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(capacidad));

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

    MedidorEficiencia::sumarMemoria(sizeof(this->idAlbum));
    MedidorEficiencia::sumarMemoria(sizeof(this->idArtista));
    MedidorEficiencia::sumarMemoria(sizeof(this->nombre) + this->nombre.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(fechaLanzamiento) + fechaLanzamiento.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(sello) + sello.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(portada) + portada.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(puntuacion));
    MedidorEficiencia::sumarMemoria(sizeof(numCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(maxCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(cancionesIDs));
    MedidorEficiencia::sumarMemoria(maxCanciones * sizeof(long));
    MedidorEficiencia::sumarMemoria(sizeof(generos));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < 4; i++){
        MedidorEficiencia::incrementarIteraciones();
        generos[i] = "N/A";
    }
}

Album::Album(const Album& otro) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(otro));

    idAlbum = otro.idAlbum;
    idArtista = otro.idArtista;
    nombre = otro.nombre;
    fechaLanzamiento = otro.fechaLanzamiento;
    sello = otro.sello;
    portada = otro.portada;
    puntuacion = otro.puntuacion;
    numCanciones = otro.numCanciones;
    maxCanciones = otro.maxCanciones;

    MedidorEficiencia::sumarMemoria(sizeof(idAlbum));
    MedidorEficiencia::sumarMemoria(sizeof(idArtista));
    MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(fechaLanzamiento) + fechaLanzamiento.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(sello) + sello.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(portada) + portada.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(puntuacion));
    MedidorEficiencia::sumarMemoria(sizeof(numCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(maxCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(generos));

    cancionesIDs = new long[maxCanciones];
    MedidorEficiencia::sumarMemoria(sizeof(cancionesIDs));
    MedidorEficiencia::sumarMemoria(maxCanciones * sizeof(long));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < numCanciones; i++){
        MedidorEficiencia::incrementarIteraciones();
        cancionesIDs[i] = otro.cancionesIDs[i];
    }

    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < 4; i++){
        MedidorEficiencia::incrementarIteraciones();
        generos[i] = otro.generos[i];
    }
}

Album::~Album() {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::restarMemoria(maxCanciones * sizeof(long));
    delete[] cancionesIDs;
}

Album& Album::operator=(const Album& otro) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(otro));
    if (this != &otro) {
        MedidorEficiencia::restarMemoria(maxCanciones * sizeof(long));
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

        MedidorEficiencia::sumarMemoria(sizeof(idAlbum));
        MedidorEficiencia::sumarMemoria(sizeof(idArtista));
        MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());
        MedidorEficiencia::sumarMemoria(sizeof(fechaLanzamiento) + fechaLanzamiento.capacity());
        MedidorEficiencia::sumarMemoria(sizeof(sello) + sello.capacity());
        MedidorEficiencia::sumarMemoria(sizeof(portada) + portada.capacity());
        MedidorEficiencia::sumarMemoria(sizeof(puntuacion));
        MedidorEficiencia::sumarMemoria(sizeof(numCanciones));
        MedidorEficiencia::sumarMemoria(sizeof(maxCanciones));
        MedidorEficiencia::sumarMemoria(sizeof(generos));

        cancionesIDs = new long[maxCanciones];
        MedidorEficiencia::sumarMemoria(sizeof(cancionesIDs));
        MedidorEficiencia::sumarMemoria(maxCanciones * sizeof(long));

        int i;
        MedidorEficiencia::sumarMemoria(sizeof(i));
        for (i = 0; i < numCanciones; i++){
            MedidorEficiencia::incrementarIteraciones();
            cancionesIDs[i] = otro.cancionesIDs[i];
        }

        MedidorEficiencia::sumarMemoria(sizeof(i));
        for (i = 0; i < 4; i++){
            MedidorEficiencia::incrementarIteraciones();
            generos[i] = otro.generos[i];
        }
    }
    return *this;
}

long Album::getIdAlbum() const {
    MedidorEficiencia::incrementarIteraciones();
    return idAlbum;
}
void Album::setIdAlbum(long id) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(id));
    idAlbum = id;
}

long Album::getIdArtista() const {
    MedidorEficiencia::incrementarIteraciones();
    return idArtista;
}
void Album::setIdArtista(long id) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(id));
    idArtista = id;
}

string Album::getNombre() const {
    MedidorEficiencia::incrementarIteraciones();
    return nombre;
}
void Album::setNombre(const string& n) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(n) + n.capacity());
    nombre = n;
}

string Album::getFechaLanzamiento() const {
    MedidorEficiencia::incrementarIteraciones();
    return fechaLanzamiento;
}
void Album::setFechaLanzamiento(const string& f) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(f) + f.capacity());
    fechaLanzamiento = f;
}

string Album::getSello() const {
    MedidorEficiencia::incrementarIteraciones();
    return sello;
}
void Album::setSello(const string& s) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(s) + s.capacity());
    sello = s;
}

string Album::getPortada() const {
    MedidorEficiencia::incrementarIteraciones();
    return portada;
}
void Album::setPortada(const string& p) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(p) + p.capacity());
    portada = p;
}

float Album::getPuntuacion() const {
    MedidorEficiencia::incrementarIteraciones();
    return puntuacion;
}
void Album::setPuntuacion(float p) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(p));
    puntuacion = p;
}

string Album::getGenero(int i) const {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(i));
    if (i < 0 || i >= 4) return "N/A";
    return generos[i];
}
void Album::setGenero(int i, const string& g) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(i));
    MedidorEficiencia::sumarMemoria(sizeof(g) + g.capacity());
    if (i >= 0 && i < 4) generos[i] = g;
}

int Album::getNumCanciones() const {
    MedidorEficiencia::incrementarIteraciones();
    return numCanciones;
}
int Album::getMaxCanciones() const {
    MedidorEficiencia::incrementarIteraciones();
    return maxCanciones;
}

long Album::getCancionID(int i) const {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(i));
    if (i < 0 || i >= numCanciones) return -1;
    return cancionesIDs[i];
}
void Album::setCancionID(int i, long id) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(i));
    MedidorEficiencia::sumarMemoria(sizeof(id));
    if (i >= 0 && i < maxCanciones)
        cancionesIDs[i] = id;
}

bool Album::agregarCancion(long idCancion) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(idCancion));
    if (numCanciones >= maxCanciones) return false;
    cancionesIDs[numCanciones++] = idCancion;
    return true;
}

bool Album::eliminarCancion(long idCancion) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(idCancion));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < numCanciones; i++) {
        MedidorEficiencia::incrementarIteraciones();
        if (cancionesIDs[i] == idCancion) {
            int j;
            MedidorEficiencia::sumarMemoria(sizeof(j));
            for (j = i; j < numCanciones - 1; j++){
                MedidorEficiencia::incrementarIteraciones();
                cancionesIDs[j] = cancionesIDs[j + 1];
            }
            numCanciones--;
            return true;
        }
    }
    return false;
}

void Album::mostrar(int esPremium) const {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(esPremium));

    cout << "\nÁlbum: " << nombre << " (" << numCanciones << " canciones)\n";

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < numCanciones; i++) {
        MedidorEficiencia::incrementarIteraciones();
        Cancion c;
        MedidorEficiencia::sumarMemoria(sizeof(c));
        c.setDatos(cancionesIDs[i], "Desconocida", "0", "ruta128.mp3", "ruta320.mp3");
        cout << "- " << c.obtenerNombre()
             << " | Duración: " << c.obtenerDuracion()
             << " | Ruta: " << c.obtenerRutaAudio(esPremium) << "\n";
    }
}

float Album::calcularDuracionTotal(int esPremium) const {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(esPremium));

    float total = 0;
    MedidorEficiencia::sumarMemoria(sizeof(total));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < numCanciones; i++) {
        MedidorEficiencia::incrementarIteraciones();
        Cancion c;
        MedidorEficiencia::sumarMemoria(sizeof(c));
        c.setDatos(cancionesIDs[i], "Desconocida", "0", "ruta128.mp3", "ruta320.mp3");
        try {
            MedidorEficiencia::incrementarIteraciones();
            total += stof(c.obtenerDuracion());
        } catch (...) {
            MedidorEficiencia::incrementarIteraciones();
        }
    }
    return total;
}

void Album::guardarEnArchivo(const string& nombreArchivo) const {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombreArchivo) + nombreArchivo.capacity());

    ofstream archivo(nombreArchivo);
    MedidorEficiencia::sumarMemoria(sizeof(archivo));
    if (!archivo.is_open()) return;

    archivo << idAlbum << ";" << nombre << ";" << idArtista << ";"
            << fechaLanzamiento << ";" << sello << ";" << puntuacion << "\n";

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < numCanciones; i++){
        MedidorEficiencia::incrementarIteraciones();
        archivo << cancionesIDs[i] << "\n";
    }

    archivo.close();
}

Album* Album::cargarAlbumes(string nombreArchivo, int& totalAlbumes) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombreArchivo) + nombreArchivo.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(totalAlbumes));

    ifstream archivo(nombreArchivo);
    MedidorEficiencia::sumarMemoria(sizeof(archivo));
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        totalAlbumes = 0;
        return nullptr;
    }
    string linea;
    MedidorEficiencia::sumarMemoria(sizeof(linea));
    totalAlbumes = 0;

    while (getline(archivo, linea)) {
        MedidorEficiencia::incrementarIteraciones();
        if (!linea.empty()) {
            totalAlbumes++;
        }
    }
    MedidorEficiencia::sumarMemoria(linea.capacity());

    if (totalAlbumes == 0) {
        archivo.close();
        return nullptr;
    }

    Album* listaAlbumes = new Album[totalAlbumes];
    MedidorEficiencia::sumarMemoria(sizeof(listaAlbumes));
    MedidorEficiencia::sumarMemoria(totalAlbumes * sizeof(Album));

    archivo.clear();
    archivo.seekg(0);

    int i = 0;
    MedidorEficiencia::sumarMemoria(sizeof(i));

    while (getline(archivo, linea) && i < totalAlbumes) {
        MedidorEficiencia::incrementarIteraciones();
        if (linea.empty()) continue;
        try {
            MedidorEficiencia::incrementarIteraciones();
            size_t pos1 = linea.find(';');
            MedidorEficiencia::sumarMemoria(sizeof(pos1));
            if (pos1 == string::npos) continue;
            string idArtistaStr = linea.substr(0, pos1);
            MedidorEficiencia::sumarMemoria(sizeof(idArtistaStr) + idArtistaStr.capacity());

            size_t pos2 = linea.find(';', pos1 + 1);
            MedidorEficiencia::sumarMemoria(sizeof(pos2));
            if (pos2 == string::npos) continue;
            string idAlbumStr = linea.substr(pos1 + 1, pos2 - (pos1 + 1));
            MedidorEficiencia::sumarMemoria(sizeof(idAlbumStr) + idAlbumStr.capacity());

            size_t pos3 = linea.find(';', pos2 + 1);
            MedidorEficiencia::sumarMemoria(sizeof(pos3));
            if (pos3 == string::npos) continue;
            string nombre = linea.substr(pos2 + 1, pos3 - (pos2 + 1));
            MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());

            string rutaPortada = linea.substr(pos3 + 1);
            MedidorEficiencia::sumarMemoria(sizeof(rutaPortada) + rutaPortada.capacity());

            listaAlbumes[i].setIdArtista(stoll(idArtistaStr));
            listaAlbumes[i].setIdAlbum(stoll(idAlbumStr));
            listaAlbumes[i].setNombre(nombre);
            listaAlbumes[i].setPortada(rutaPortada);
            i++;
        } catch (const invalid_argument& e) {
            MedidorEficiencia::incrementarIteraciones();
            cout << "Error de formato numerico en linea de album: " << linea << " (" << e.what() << ")" << endl;
        } catch (const out_of_range& e) {
            MedidorEficiencia::incrementarIteraciones();
            cout << "Error de rango numerico en linea de album: " << linea << " (" << e.what() << ")" << endl;
        } catch (...) {
            MedidorEficiencia::incrementarIteraciones();
            cout << "Error desconocido al parsear linea de album: " << linea << endl;
        }
    }
    MedidorEficiencia::sumarMemoria(linea.capacity());
    archivo.close();
    totalAlbumes = i;
    return listaAlbumes;
}

Album* Album::buscarAlbumPorIDs(Album* listaAlbumes, int totalAlbumes, long idArtista, long idAlbumNum) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(listaAlbumes));
    MedidorEficiencia::sumarMemoria(sizeof(totalAlbumes));
    MedidorEficiencia::sumarMemoria(sizeof(idArtista));
    MedidorEficiencia::sumarMemoria(sizeof(idAlbumNum));

    if (listaAlbumes == nullptr) return nullptr;

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < totalAlbumes; i++) {
        MedidorEficiencia::incrementarIteraciones();
        if (listaAlbumes[i].getIdArtista() == idArtista && listaAlbumes[i].getIdAlbum() == idAlbumNum) {
            return &listaAlbumes[i];
        }
    }
    return nullptr;
}
