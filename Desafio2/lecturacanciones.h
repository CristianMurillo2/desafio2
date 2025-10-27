#ifndef LECTURACANCIONES_H
#define LECTURACANCIONES_H

#include "cancion.h"
#include <string>
using namespace std;

class LecturaCanciones
{
private:
    Cancion* listaCanciones;
    int totalCanciones;

public:
    LecturaCanciones();
    ~LecturaCanciones();

    void cargarCanciones(string nombreArchivo);

    Cancion* buscarCancionPorID(long idBuscado);

    Cancion* obtenerCancionAleatoria();
};

#endif
