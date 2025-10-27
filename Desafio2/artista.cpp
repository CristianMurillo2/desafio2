#include "artista.h"
#include <iostream>
#include "eficiencia.h"

Artista::Artista() {
    MedidorEficiencia::incrementarIteraciones();
    idArtista = 0;
    nombre = "";
    pais = "";
    edad = 0;
    seguidores = 0;
    posicionTendencias = 0;

    MedidorEficiencia::sumarMemoria(sizeof(idArtista));
    MedidorEficiencia::sumarMemoria(sizeof(nombre) + nombre.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(pais) + pais.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(edad));
    MedidorEficiencia::sumarMemoria(sizeof(seguidores));
    MedidorEficiencia::sumarMemoria(sizeof(posicionTendencias));
}

Artista::~Artista() {
    MedidorEficiencia::incrementarIteraciones();
}

void Artista::setDatos(long id, string nom, string p, int ed, int seg, int pos) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(id));
    MedidorEficiencia::sumarMemoria(sizeof(nom) + nom.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(p) + p.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(ed));
    MedidorEficiencia::sumarMemoria(sizeof(seg));
    MedidorEficiencia::sumarMemoria(sizeof(pos));

    idArtista = id;
    nombre = nom;
    pais = p;
    edad = ed;
    seguidores = seg;
    posicionTendencias = pos;
}

long Artista::obtenerID() {
    MedidorEficiencia::incrementarIteraciones();
    return idArtista;
}
string Artista::obtenerNombre() {
    MedidorEficiencia::incrementarIteraciones();
    return nombre;
}
string Artista::obtenerPais() {
    MedidorEficiencia::incrementarIteraciones();
    return pais;
}
int Artista::obtenerEdad() {
    MedidorEficiencia::incrementarIteraciones();
    return edad;
}
int Artista::obtenerSeguidores() {
    MedidorEficiencia::incrementarIteraciones();
    return seguidores;
}
int Artista::obtenerPosicionTendencias() {
    MedidorEficiencia::incrementarIteraciones();
    return posicionTendencias;
}


Artista& Artista::operator=(const Artista& otro) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(otro));

    if (this != &otro) {
        this->idArtista = otro.idArtista;
        this->nombre = otro.nombre;
        this->pais = otro.pais;
        this->edad = otro.edad;
        this->seguidores = otro.seguidores;
        this->posicionTendencias = otro.posicionTendencias;
    }
    return *this;
}
