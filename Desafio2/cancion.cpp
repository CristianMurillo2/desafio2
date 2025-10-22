#include "cancion.h"


Cancion::Cancion() {
    idCancion = 0;
    nombre = "";
    duracion = "00:00";
    ruta128 = "";
    ruta320 = "";
}

void Cancion::setDatos(long id, string nom, string dur, string r128, string r320) {
    idCancion = id;
    nombre = nom;
    duracion = dur;
    ruta128 = r128;
    ruta320 = r320;
}

long Cancion::obtenerID() { return idCancion; }
string Cancion::obtenerNombre() { return nombre; }
string Cancion::obtenerDuracion() { return duracion; }
string Cancion::obtenerRutaAudio(int esPremium) {
    if (esPremium == 1) {
        return ruta320;
    } else {
        return ruta128;
    }
}


Cancion& Cancion::operator=(const Cancion& otra) {
    // 1. Evitar auto-asignación (ej: c1 = c1)
    if (this != &otra) {
        // 2. Copiar todos los atributos
        this->idCancion = otra.idCancion;
        this->nombre = otra.nombre;
        this->duracion = otra.duracion;
        this->ruta128 = otra.ruta128;
        this->ruta320 = otra.ruta320;
    }
    return *this;
}
