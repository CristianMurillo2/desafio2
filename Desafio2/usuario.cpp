#include "usuario.h"

Usuario::Usuario() {
    nombre = "";
    contrasena = "";
    premium = 0;
}

Usuario::Usuario(string n, string c, int a) {
    nombre = n;
    contrasena = c;
    premium = a;
}

void Usuario::setDatos(string n, string c, int a) {
    nombre = n;
    contrasena = c;
    premium = a;
}

string Usuario::obtenerNombre() { return nombre; }
string Usuario::obtenerContrasena() { return contrasena; }
int Usuario::obtenerPremium() { return premium; }

LecturaUsuario::LecturaUsuario() {
    usuarios = nullptr;
    cantidad = 0;
}

LecturaUsuario::~LecturaUsuario() {
    delete[] usuarios;
}

void LecturaUsuario::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    int contador = 0;
    while (getline(archivo, linea)) {
        if (!linea.empty()) contador++;
    }

    delete[] usuarios;
    usuarios = new Usuario[contador];
    cantidad = contador;

    archivo.clear();
    archivo.seekg(0);

    int i = 0;
    while (getline(archivo, linea) && i < cantidad) {
        if (linea.empty()) continue;

        int pos1 = linea.find(',');
        int pos2 = linea.find(',', pos1 + 1);



        if (pos1 == -1 || pos2 == -1) continue;

        string nombre = linea.substr(0, pos1);
        string contrasena = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string premiumStr = linea.substr(pos2 + 1);

        int premium = stoi(premiumStr);
        usuarios[i].setDatos(nombre, contrasena, premium);
        i++;
    }

    archivo.close();
}

int LecturaUsuario::verificarUsuario(const string* datos){
    string nombreIngresado = datos[0];
    string contrasenaIngresada = datos[1];

    for (int i = 0; i < cantidad; i++) {
        if (usuarios[i].obtenerNombre() == nombreIngresado && usuarios[i].obtenerContrasena() == contrasenaIngresada) {
            return usuarios[i].obtenerPremium();
        }
    }
    cout << "Usuario o contrasena incorrectos. Intentelo nuevamente." << endl << endl;
    return -1;
}
