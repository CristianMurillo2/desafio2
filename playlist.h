#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include "cancion.h"

class Playlist {
private:
    std::string nombre;
    long* cancionesIDs;          // Solo guarda los IDs de las canciones
    int numCanciones;
    int maxCanciones;
    int indiceActual;
    int historial[4];
    int posHistorial;
    int cancionesEnHistorial;

public:
    // Constructores y destructor
    Playlist();
    Playlist(const std::string& nombre, int capacidadMax);
    Playlist(const Playlist& otra);
    ~Playlist();

    Playlist& operator=(const Playlist& otra);

    // --- Getters y Setters ---
    std::string getNombre() const;
    void setNombre(const std::string& nuevoNombre);

    int getNumCanciones() const;
    int getMaxCanciones() const;
    int getIndiceActual() const;
    void setIndiceActual(int indice);

    long getCancionID(int indice) const;
    void setCancionID(int indice, long id);

    // --- Funcionalidad ---
    bool agregarCancion(long idCancion);
    bool eliminarCancion(long idCancion);
    void mostrar(int esPremium) const;

    Cancion reproducirActual(int esPremium);
    Cancion siguiente(int esPremium);
    Cancion anterior(int esPremium);

    // --- Persistencia ---
    void guardarEnArchivo(const std::string& nombreArchivo) const;
    static Playlist cargarDesdeArchivo(const std::string& nombreArchivo, int capacidadMax);
};

#endif
