#ifndef LECTURA_USUARIO_H
#define LECTURA_USUARIO_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Usuario {
private:
    string nombre;
    string contrasena;
    int premium; // 1 o 0

public:
    Usuario();
    Usuario(string n, string c, int a);

    void setDatos(string n, string c, int a);
    string obtenerNombre();
    string obtenerContrasena();
    int obtenerPremium();
};

class LecturaUsuario {
private:
    Usuario* usuarios; // arreglo dinámico
    int cantidad;      // número de usuarios cargados

public:
    LecturaUsuario();
    ~LecturaUsuario();

    void cargarDesdeArchivo(const string& nombreArchivo);
    int verificarUsuario(const string* datos); // retorna 1, 0 o -1 si no existe
};

#endif
