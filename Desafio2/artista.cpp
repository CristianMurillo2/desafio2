#include "artista.h"
#include <iostream>

Artista::Artista() {
    idArtista = 0;
    nombre = "";
    pais = "";
    edad = 0;
    seguidores = 0;
    posicionTendencias = 0;
}

Artista::~Artista() {

}

void Artista::setDatos(long id, string nom, string p, int ed, int seg, int pos) {
    idArtista = id;
    nombre = nom;
    pais = p;
    edad = ed;
    seguidores = seg;
    posicionTendencias = pos;
}

long Artista::obtenerID() { return idArtista; }
string Artista::obtenerNombre() { return nombre; }
string Artista::obtenerPais() { return pais; }
int Artista::obtenerEdad() { return edad; }
int Artista::obtenerSeguidores() { return seguidores; }
int Artista::obtenerPosicionTendencias() { return posicionTendencias; }


Artista& Artista::operator=(const Artista& otro) {

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
