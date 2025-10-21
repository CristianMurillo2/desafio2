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
    int premium;

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
    Usuario* usuarios;
    int cantidad;

public:
    LecturaUsuario();
    ~LecturaUsuario();

    void cargarDesdeArchivo(const string& nombreArchivo);
    int verificarUsuario(const string* datos);
};

#endif
