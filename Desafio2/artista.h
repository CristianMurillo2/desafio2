#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>
using namespace std;

class Artista
{
private:
    long idArtista;
    string nombre;
    string pais;
    int edad;
    int seguidores;
    int posicionTendencias;

public:
    Artista();

    ~Artista();

    void setDatos(long id, string nom, string p, int ed, int seg, int pos);

    long obtenerID();
    string obtenerNombre();
    string obtenerPais();
    int obtenerEdad();
    int obtenerSeguidores();
    int obtenerPosicionTendencias();

    Artista& operator=(const Artista& otro);
};

#endif
