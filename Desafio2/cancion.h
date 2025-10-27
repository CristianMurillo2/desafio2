#ifndef CANCION_H
#define CANCION_H

#include <string>
using namespace std;

class Cancion
{
private:
    long idCancion;
    string nombre;
    string duracion;
    string ruta128;
    string ruta320;

public:
    Cancion();

    void setDatos(long id, string nom, string dur, string r128, string r320);

    long obtenerID();
    string obtenerNombre();
    string obtenerDuracion();

    string obtenerRutaAudio(int esPremium);

    Cancion& operator=(const Cancion& otra);
};

#endif
