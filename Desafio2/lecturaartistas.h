#ifndef LECTURAARTISTAS_H
#define LECTURAARTISTAS_H
#include "artista.h"
#include <string>
using namespace std;

class LecturaArtistas
{
private:
    Artista* listaArtistas;
    int totalArtistas;

public:
    LecturaArtistas();

    ~LecturaArtistas();

    void cargarArtistas(string nombreArchivo);

    Artista* buscarArtistaPorID(long idBuscado);
};

#endif
