#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include "cancion.h"

class LecturaCanciones;

class Playlist {
private:
    std::string nombre;
    long* cancionesIDs;
    int numCanciones;
    int maxCanciones;
    int indiceActual;
    int historial[6];
    int posHistorial;
    int cancionesEnHistorial;

    Cancion _reproducirIndiceActual(int esPremium, LecturaCanciones& gestor);

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
    void setIndiceActual(int indice);

    long getCancionID(int indice) const;
    void setCancionID(int indice, long id);

    bool agregarCancion(long idCancion);
    bool eliminarCancion(long idCancion);
    void mostrar(int esPremium) const;

    Cancion reproducirActual(int esPremium, LecturaCanciones& gestor);
    Cancion siguiente(int esPremium, LecturaCanciones& gestor);
    Cancion anterior(int esPremium, LecturaCanciones& gestor);
    Cancion reproducirAleatoria(int esPremium, LecturaCanciones& gestor);

    void guardarEnArchivo(const std::string& nombreArchivo) const;
    static Playlist cargarDesdeArchivo(const std::string& nombreArchivo, int capacidadMax);
};

#endif
