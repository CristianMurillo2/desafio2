#include "playlist.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "lecturacanciones.h"
#include "eficiencia.h"

using namespace std;

Playlist::Playlist() {
    MedidorEficiencia::incrementarIteraciones();
    nombre = "Favoritos";
    maxCanciones = 20;
    numCanciones = 0;
    indiceActual = 0;
    cancionesIDs = new long[maxCanciones];
    posHistorial = 0;
    cancionesEnHistorial = 0;

    MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(maxCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(numCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(indiceActual));
    MedidorEficiencia::sumarMemoria(sizeof(cancionesIDs));
    MedidorEficiencia::sumarMemoria(maxCanciones * sizeof(long));
    MedidorEficiencia::sumarMemoria(sizeof(posHistorial));
    MedidorEficiencia::sumarMemoria(sizeof(cancionesEnHistorial));
    MedidorEficiencia::sumarMemoria(sizeof(historial));
}

Playlist::Playlist(const std::string& nombre, int capacidadMax) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(capacidadMax));

    this->nombre = nombre;
    maxCanciones = capacidadMax > 0 ? capacidadMax : 20;
    numCanciones = 0;
    indiceActual = 0;
    cancionesIDs = new long[maxCanciones];
    posHistorial = 0;
    cancionesEnHistorial = 0;

    MedidorEficiencia::sumarMemoria(sizeof(this->nombre) + this->nombre.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(maxCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(numCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(indiceActual));
    MedidorEficiencia::sumarMemoria(sizeof(cancionesIDs));
    MedidorEficiencia::sumarMemoria(maxCanciones * sizeof(long));
    MedidorEficiencia::sumarMemoria(sizeof(posHistorial));
    MedidorEficiencia::sumarMemoria(sizeof(cancionesEnHistorial));
    MedidorEficiencia::sumarMemoria(sizeof(historial));
}

Playlist::Playlist(const Playlist& otra) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(otra));

    nombre = otra.nombre;
    maxCanciones = otra.maxCanciones;
    numCanciones = otra.numCanciones;
    indiceActual = otra.indiceActual;
    posHistorial = otra.posHistorial;
    cancionesEnHistorial = otra.cancionesEnHistorial;

    MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(maxCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(numCanciones));
    MedidorEficiencia::sumarMemoria(sizeof(indiceActual));
    MedidorEficiencia::sumarMemoria(sizeof(posHistorial));
    MedidorEficiencia::sumarMemoria(sizeof(cancionesEnHistorial));
    MedidorEficiencia::sumarMemoria(sizeof(historial));

    cancionesIDs = new long[maxCanciones];
    MedidorEficiencia::sumarMemoria(sizeof(cancionesIDs));
    MedidorEficiencia::sumarMemoria(maxCanciones * sizeof(long));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < numCanciones; i++){
        MedidorEficiencia::incrementarIteraciones();
        cancionesIDs[i] = otra.cancionesIDs[i];
    }

    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < 6; i++){
        MedidorEficiencia::incrementarIteraciones();
        historial[i] = otra.historial[i];
    }
}

Playlist::~Playlist() {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::restarMemoria(maxCanciones * sizeof(long));
    delete[] cancionesIDs;
}

Playlist& Playlist::operator=(const Playlist& otra) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(otra));

    if (this != &otra) {
        MedidorEficiencia::restarMemoria(maxCanciones * sizeof(long));
        delete[] cancionesIDs;

        nombre = otra.nombre;
        maxCanciones = otra.maxCanciones;
        numCanciones = otra.numCanciones;
        indiceActual = otra.indiceActual;
        posHistorial = otra.posHistorial;
        cancionesEnHistorial = otra.cancionesEnHistorial;

        MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());
        MedidorEficiencia::sumarMemoria(sizeof(maxCanciones));
        MedidorEficiencia::sumarMemoria(sizeof(numCanciones));
        MedidorEficiencia::sumarMemoria(sizeof(indiceActual));
        MedidorEficiencia::sumarMemoria(sizeof(posHistorial));
        MedidorEficiencia::sumarMemoria(sizeof(cancionesEnHistorial));
        MedidorEficiencia::sumarMemoria(sizeof(historial));

        cancionesIDs = new long[maxCanciones];
        MedidorEficiencia::sumarMemoria(sizeof(cancionesIDs));
        MedidorEficiencia::sumarMemoria(maxCanciones * sizeof(long));

        int i;
        MedidorEficiencia::sumarMemoria(sizeof(i));
        for (i = 0; i < numCanciones; i++){
            MedidorEficiencia::incrementarIteraciones();
            cancionesIDs[i] = otra.cancionesIDs[i];
        }

        MedidorEficiencia::sumarMemoria(sizeof(i));
        for (i = 0; i < 6; i++){
            MedidorEficiencia::incrementarIteraciones();
            historial[i] = otra.historial[i];
        }
    }
    return *this;
}

std::string Playlist::getNombre() const {
    MedidorEficiencia::incrementarIteraciones();
    return nombre;
}
void Playlist::setNombre(const std::string& nuevoNombre) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nuevoNombre) + nuevoNombre.capacity());
    nombre = nuevoNombre;
    MedidorEficiencia::sumarMemoria(nombre.capacity());
}
int Playlist::getNumCanciones() const {
    MedidorEficiencia::incrementarIteraciones();
    return numCanciones;
}
int Playlist::getMaxCanciones() const {
    MedidorEficiencia::incrementarIteraciones();
    return maxCanciones;
}
int Playlist::getIndiceActual() const {
    MedidorEficiencia::incrementarIteraciones();
    return indiceActual;
}
void Playlist::setIndiceActual(int indice) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(indice));
    if (indice >= 0 && indice < numCanciones) indiceActual = indice;
}
long Playlist::getCancionID(int indice) const {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(indice));
    if (indice >= 0 && indice < numCanciones) return cancionesIDs[indice];
    return 0;
}
void Playlist::setCancionID(int indice, long id) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(indice));
    MedidorEficiencia::sumarMemoria(sizeof(id));
    if (indice >= 0 && indice < numCanciones) cancionesIDs[indice] = id;
}


bool Playlist::agregarCancion(long idCancion) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(idCancion));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < numCanciones; i++) {
        MedidorEficiencia::incrementarIteraciones();
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
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(idCancion));

    int indice = -1;
    MedidorEficiencia::sumarMemoria(sizeof(indice));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < numCanciones; i++) {
        MedidorEficiencia::incrementarIteraciones();
        if (cancionesIDs[i] == idCancion) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        return false;
    }

    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = indice; i < numCanciones - 1; i++) {
        MedidorEficiencia::incrementarIteraciones();
        cancionesIDs[i] = cancionesIDs[i + 1];
    }
    numCanciones--;
    return true;
}

void Playlist::mostrar(int esPremium) const {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(esPremium));

    cout << "Playlist: " << nombre << endl;
    if (numCanciones == 0) {
        cout << "(Vacia)" << endl;
        return;
    }

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < numCanciones; i++) {
        MedidorEficiencia::incrementarIteraciones();
        cout << "  " << i + 1 << ". ID: " << cancionesIDs[i] << endl;
    }
}

Cancion Playlist::_reproducirIndiceActual(int esPremium, LecturaCanciones& gestor) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(esPremium));
    MedidorEficiencia::sumarMemoria(sizeof(gestor));

    if (numCanciones == 0) return Cancion();

    long idActual = cancionesIDs[indiceActual];
    MedidorEficiencia::sumarMemoria(sizeof(idActual));
    Cancion* cancionPtr = gestor.buscarCancionPorID(idActual);
    MedidorEficiencia::sumarMemoria(sizeof(cancionPtr));

    if (cancionPtr != nullptr) {
        return *cancionPtr;
    } else {
        return Cancion();
    }
}

Cancion Playlist::reproducirActual(int esPremium, LecturaCanciones& gestor) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(esPremium));
    MedidorEficiencia::sumarMemoria(sizeof(gestor));

    if (numCanciones == 0) return Cancion();

    return _reproducirIndiceActual(esPremium, gestor);
}

Cancion Playlist::siguiente(int esPremium, LecturaCanciones& gestor) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(esPremium));
    MedidorEficiencia::sumarMemoria(sizeof(gestor));

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
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(esPremium));
    MedidorEficiencia::sumarMemoria(sizeof(gestor));

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

Cancion Playlist::reproducirAleatoria(int esPremium, LecturaCanciones& gestor) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(esPremium));
    MedidorEficiencia::sumarMemoria(sizeof(gestor));

    if (numCanciones == 0) return Cancion();

    historial[posHistorial] = indiceActual;
    posHistorial = (posHistorial + 1) % 6;
    if (cancionesEnHistorial < 6) {
        cancionesEnHistorial++;
    }

    int nuevoIndice;
    MedidorEficiencia::sumarMemoria(sizeof(nuevoIndice));
    if (numCanciones > 1) {
        do {
            MedidorEficiencia::incrementarIteraciones();
            nuevoIndice = rand() % numCanciones;
        } while (nuevoIndice == indiceActual);
    } else {
        nuevoIndice = 0;
    }

    indiceActual = nuevoIndice;

    return _reproducirIndiceActual(esPremium, gestor);
}


void Playlist::guardarEnArchivo(const std::string& nombreArchivo) const {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombreArchivo) + nombreArchivo.capacity());

    ofstream archivo(nombreArchivo);
    MedidorEficiencia::sumarMemoria(sizeof(archivo));
    if (!archivo.is_open()) return;

    archivo << nombre << '\n';

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < numCanciones; i++){
        MedidorEficiencia::incrementarIteraciones();
        archivo << cancionesIDs[i] << '\n';
    }

    archivo.close();
}

Playlist Playlist::cargarDesdeArchivo(const std::string& nombreArchivo, int capacidadMax) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombreArchivo) + nombreArchivo.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(capacidadMax));

    Playlist pl("Cargada", capacidadMax);
    MedidorEficiencia::sumarMemoria(sizeof(pl));

    ifstream archivo(nombreArchivo);
    MedidorEficiencia::sumarMemoria(sizeof(archivo));
    if (!archivo.is_open()) {
        return pl;
    }

    getline(archivo, pl.nombre);
    MedidorEficiencia::sumarMemoria(pl.nombre.capacity());

    long id;
    MedidorEficiencia::sumarMemoria(sizeof(id));
    while (archivo >> id) {
        MedidorEficiencia::incrementarIteraciones();
        pl.agregarCancion(id);
    }

    archivo.close();
    return pl;
}
