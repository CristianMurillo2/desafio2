#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "cancion.h"

class Album {
private:
    long idAlbum;
    long idArtista;
    std::string nombre;
    std::string fechaLanzamiento;
    std::string sello;
    std::string portada;
    float puntuacion;
    std::string generos[4];

    long* cancionesIDs;
    int numCanciones;
    int maxCanciones;

public:    Album();
    Album(long idAlbum, long idArtista, const std::string& nombre, int capacidad);
    Album(const Album& otro);
    ~Album();

    Album& operator=(const Album& otro);
    long getIdAlbum() const;
    void setIdAlbum(long id);

    long getIdArtista() const;
    void setIdArtista(long id);

    std::string getNombre() const;
    void setNombre(const std::string& n);

    std::string getFechaLanzamiento() const;
    void setFechaLanzamiento(const std::string& f);

    std::string getSello() const;
    void setSello(const std::string& s);

    std::string getPortada() const;
    void setPortada(const std::string& p);

    float getPuntuacion() const;
    void setPuntuacion(float p);

    std::string getGenero(int i) const;
    void setGenero(int i, const std::string& g);

    int getNumCanciones() const;
    int getMaxCanciones() const;

    long getCancionID(int i) const;
    void setCancionID(int i, long id);

    bool agregarCancion(long idCancion);
    bool eliminarCancion(long idCancion);
    void mostrar(int esPremium) const;
    float calcularDuracionTotal(int esPremium) const;

    void guardarEnArchivo(const std::string& nombreArchivo) const;
    static Album cargarDesdeArchivo(const std::string& nombreArchivo, int capacidad);
};

#endif
