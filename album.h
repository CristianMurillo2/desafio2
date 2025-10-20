#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "Cancion.h"

class Album {
private:
    int idAlbum;
    int idArtista;
    std::string nombre;
    std::string fechaLanzamiento;
    std::string sello;
    std::string portada;
    float puntuacion;
    std::string generos[4];
    Cancion** canciones;
    int numCanciones;
    int maxCanciones;

public:
    Album();
    Album(int idAlbum, int idArtista, const std::string& nombre, int capacidad);
    Album(const Album& otro);
    ~Album();
    Album& operator=(const Album& otro);
    int getIdAlbum() const;
    void setIdAlbum(int id);

    int getIdArtista() const;
    void setIdArtista(int id);

    std::string getNombre() const;
    void setNombre(const std::string& nombre);

    std::string getFechaLanzamiento() const;
    void setFechaLanzamiento(const std::string& fecha);

    std::string getSello() const;
    void setSello(const std::string& sello);

    std::string getPortada() const;
    void setPortada(const std::string& portada);

    float getPuntuacion() const;
    void setPuntuacion(float puntuacion);

    std::string getGenero(int i) const;
    void setGenero(int i, const std::string& genero);

    int getNumCanciones() const;

    bool agregarCancion(Cancion* c);
    Cancion* buscarCancion(int id) const;
    float calcularDuracionTotal() const;
    void mostrarInfo() const;
};

#endif
