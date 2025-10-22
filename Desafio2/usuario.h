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
    string getNombre() const;
    void setNombre(const string &newNombre);
    void setContrasena(const string &newContrasena);
    string getContrasena() const;
    int getPremium() const;
    void setPremium(int newPremium);
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
