#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "cancion.h"

class Album {
private:
    long idAlbum;
    long idArtista;
    string nombre;
    string fechaLanzamiento;
    string sello;
    string portada;
    float puntuacion;
    string generos[4];

    long* cancionesIDs;
    int numCanciones;
    int maxCanciones;

public:    Album();
    Album(long idAlbum, long idArtista, const string& nombre, int capacidad);
    Album(const Album& otro);
    ~Album();

    Album& operator=(const Album& otro);
    long getIdAlbum() const;
    void setIdAlbum(long id);

    long getIdArtista() const;
    void setIdArtista(long id);

    string getNombre() const;
    void setNombre(const string& n);

    string getFechaLanzamiento() const;
    void setFechaLanzamiento(const string& f);

    string getSello() const;
    void setSello(const string& s);

    string getPortada() const;
    void setPortada(const string& p);

    float getPuntuacion() const;
    void setPuntuacion(float p);

    string getGenero(int i) const;
    void setGenero(int i, const string& g);

    int getNumCanciones() const;
    int getMaxCanciones() const;

    long getCancionID(int i) const;
    void setCancionID(int i, long id);

    bool agregarCancion(long idCancion);
    bool eliminarCancion(long idCancion);
    void mostrar(int esPremium) const;
    float calcularDuracionTotal(int esPremium) const;

    void guardarEnArchivo(const string& nombreArchivo) const;

    static Album* cargarAlbumes(string nombreArchivo, int& totalAlbumes);
    static Album* buscarAlbumPorIDs(Album* listaAlbumes, int totalAlbumes, long idArtista, long idAlbumNum);
};

#endif
