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
    string usuarioSeguido;

public:
    Usuario();

    Usuario(string n, string c, int a);
    void ponerDatos(string n, string c, int a);

    Usuario(string n, string c, int a, string seguido);
    void ponerDatos(string n, string c, int a, string seguido);

    string obtenerNombre();
    string obtenerContrasena();
    int obtenerPremium();
    string obtenerNombre() const;
    void ponerNombre(const string &newNombre);
    void ponerContrasena(const string &newContrasena);
    string obtenerContrasena() const;
    int obtenerPremium() const;
    void ponerPremium(int newPremium);

    string obtenerUsuarioSeguido() const;
    void ponerUsuarioSeguido(const string &newUsuarioSeguido);
};

class LecturaUsuario {
private:
    Usuario* usuarios;
    int cantidad;
    string nombreArchivo;

public:
    LecturaUsuario();
    ~LecturaUsuario();

    void cargarDesdeArchivo(const string& nombreArchivo);

    int verificarUsuario(const string* datos);

    Usuario* obtenerUsuario(string nombre);
    void guardarEnArchivo();
    void seguirUsuario(string nombreUsuario, string usuarioASeguir);
    void dejarDeSeguir(string nombreUsuario);
};

#endif
