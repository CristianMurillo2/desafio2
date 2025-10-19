#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include "Cancion.h"

class Playlist {
private:
    std::string nombre;
    Cancion** canciones;
    int numCanciones;
    int maxCanciones;
    int indiceActual;
    int historial[4];
    int posHistorial;
    int cancionesEnHistorial;

public:
    Playlist();
    Playlist(const std::string& nombre, int capacidadMax);
    Playlist(const Playlist& otra);
    ~Playlist();
    Playlist& operator=(const Playlist& otra);
    std::string getNombre() const;
    void setNombre(const std::string& nuevoNombre);
    int getNumCanciones() const;
    int getMaxCanciones() const;
    int getIndiceActual() const;
    bool agregarCancion(Cancion* c);
    bool eliminarCancion(int idCancion);
    void mostrar() const;
    Cancion* siguiente();
    Cancion* anterior();
};

#endif
