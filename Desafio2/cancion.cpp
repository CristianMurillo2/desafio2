#include "cancion.h"
#include "eficiencia.h"

Cancion::Cancion() {
    MedidorEficiencia::incrementarIteraciones();
    idCancion = 0;
    nombre = "";
    duracion = "00:00";
    ruta128 = "";
    ruta320 = "";

    MedidorEficiencia::sumarMemoria(sizeof(idCancion));
    MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(duracion) + duracion.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(ruta128) + ruta128.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(ruta320) + ruta320.capacity());
}

void Cancion::setDatos(long id, string nom, string dur, string r128, string r320) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(id));
    MedidorEficiencia::sumarMemoria(sizeof(nom) + nom.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(dur) + dur.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(r128) + r128.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(r320) + r320.capacity());

    idCancion = id;
    nombre = nom;
    duracion = dur;
    ruta128 = r128;
    ruta320 = r320;
}

long Cancion::obtenerID() {
    MedidorEficiencia::incrementarIteraciones();
    return idCancion;
}
string Cancion::obtenerNombre() {
    MedidorEficiencia::incrementarIteraciones();
    return nombre;
}
string Cancion::obtenerDuracion() {
    MedidorEficiencia::incrementarIteraciones();
    return duracion;
}
string Cancion::obtenerRutaAudio(int esPremium) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(esPremium));

    if (esPremium == 1) {
        return ruta320;
    } else {
        return ruta128;
    }
}


Cancion& Cancion::operator=(const Cancion& otra) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(otra));

    if (this != &otra) {
        this->idCancion = otra.idCancion;
        this->nombre = otra.nombre;
        this->duracion = otra.duracion;
        this->ruta128 = otra.ruta128;
        this->ruta320 = otra.ruta320;
    }
    return *this;
}
