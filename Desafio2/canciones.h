#ifndef CANCIONES_H
#define CANCIONES_H

#include <string>
using namespace std;

class canciones
{
public:
    canciones();
    ~canciones();

    string* buscarCancionPorID(long idBuscado, int esPremium);
};

#endif // CANCIONES_H
