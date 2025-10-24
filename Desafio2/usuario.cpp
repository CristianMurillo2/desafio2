#include "usuario.h"
#include <stdexcept>

string Usuario::obtenerNombre() const { return nombre; }
void Usuario::ponerNombre(const string &newNombre) { nombre = newNombre; }
void Usuario::ponerContrasena(const string &newContrasena) { contrasena = newContrasena; }
string Usuario::obtenerContrasena() const { return contrasena; }
int Usuario::obtenerPremium() const { return premium; }
void Usuario::ponerPremium(int newPremium) { premium = newPremium; }
string Usuario::obtenerNombre() { return nombre; }
string Usuario::obtenerContrasena() { return contrasena; }
int Usuario::obtenerPremium() { return premium; }

Usuario::Usuario() {
    nombre = "";
    contrasena = "";
    premium = 0;
    usuarioSeguido = "";
}

Usuario::Usuario(string n, string c, int a) {
    nombre = n;
    contrasena = c;
    premium = a;
    usuarioSeguido = "";
}

void Usuario::ponerDatos(string n, string c, int a) {
    nombre = n;
    contrasena = c;
    premium = a;
    usuarioSeguido = "";
}

Usuario::Usuario(string n, string c, int a, string seguido) {
    nombre = n;
    contrasena = c;
    premium = a;
    if (premium == 1) {
        usuarioSeguido = seguido;
    } else {
        usuarioSeguido = "";
    }
}

void Usuario::ponerDatos(string n, string c, int a, string seguido) {
    nombre = n;
    contrasena = c;
    premium = a;
    if (premium == 1) {
        usuarioSeguido = seguido;
    } else {
        usuarioSeguido = "";
    }
}

string Usuario::obtenerUsuarioSeguido() const {
    return usuarioSeguido;
}

void Usuario::ponerUsuarioSeguido(const string &newUsuarioSeguido) {
    if (premium == 1) {
        usuarioSeguido = newUsuarioSeguido;
    } else {
        cout << endl << "Error: Los usuarios estandar no pueden seguir a otros." << endl;
        usuarioSeguido = "";
    }
}

LecturaUsuario::LecturaUsuario() {
    usuarios = nullptr;
    cantidad = 0;
    nombreArchivo = "";
}

LecturaUsuario::~LecturaUsuario() {
    delete[] usuarios;
}

void LecturaUsuario::cargarDesdeArchivo(const string& nombreArchivo)
{
    this->nombreArchivo = nombreArchivo;

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << endl << "Error al abrir el archivo: " << nombreArchivo << endl;
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

        string nombre, contrasena, premiumStr, usuarioSeguido;
        int premium;

        size_t pos1 = linea.find(',');
        if (pos1 == string::npos) continue;
        nombre = linea.substr(0, pos1);

        size_t pos2 = linea.find(',', pos1 + 1);
        if (pos2 == string::npos) continue;
        contrasena = linea.substr(pos1 + 1, pos2 - pos1 - 1);

        size_t pos3 = linea.find(',', pos2 + 1);

        try {
            if (pos3 == string::npos) {
                premiumStr = linea.substr(pos2 + 1);
                premium = stoi(premiumStr);

                usuarios[i].ponerDatos(nombre, contrasena, premium);

            } else {
                premiumStr = linea.substr(pos2 + 1, pos3 - pos2 - 1);
                usuarioSeguido = linea.substr(pos3 + 1);
                premium = stoi(premiumStr);

                usuarios[i].ponerDatos(nombre, contrasena, premium, usuarioSeguido);
            }
            i++;

        } catch (const std::invalid_argument& e) {
            cout << endl << "Error al convertir premium en linea: " << linea << endl;
        }
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
    cout << endl << "Usuario o contrasena incorrectos." << endl;
    return -1;
}

Usuario* LecturaUsuario::obtenerUsuario(string nombre) {
    for (int i = 0; i < cantidad; i++) {
        if (usuarios[i].obtenerNombre() == nombre) {
            return &usuarios[i];
        }
    }
    return nullptr;
}

void LecturaUsuario::guardarEnArchivo() {
    if (nombreArchivo.empty()) {
        cout << endl << "Error: No se ha cargado ningún archivo." << endl;
        return;
    }

    ofstream archivo(this->nombreArchivo);
    if (!archivo.is_open()) {
        cout << endl << "Error: No se pudo abrir el archivo para guardar: " << this->nombreArchivo << endl;
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        archivo << usuarios[i].obtenerNombre() << ",";
        archivo << usuarios[i].obtenerContrasena() << ",";
        archivo << usuarios[i].obtenerPremium();

        string seguido = usuarios[i].obtenerUsuarioSeguido();

        if (usuarios[i].obtenerPremium() == 1 && !seguido.empty()) {
            archivo << "," << seguido;
        }

        if (i < cantidad - 1) {
            archivo << endl;
        }
    }
    archivo.close();
}

void LecturaUsuario::seguirUsuario(string nombreUsuario, string usuarioASeguir) {
    Usuario* usuario = obtenerUsuario(nombreUsuario);
    if (usuario == nullptr) {
        cout << endl << "Error: No se encontro al usuario " << nombreUsuario << endl;
        return;
    }

    if (usuario->obtenerPremium() == 0) {
        cout << endl << "Lo sentimos, solo los usuarios premium pueden seguir a otros." << endl;
        return;
    }

    Usuario* usuarioSeguido = obtenerUsuario(usuarioASeguir);
    if (usuarioSeguido == nullptr) {
        cout << endl << "Error: El usuario '" << usuarioASeguir << "' no existe." << endl;
        return;
    }
    if (nombreUsuario == usuarioASeguir) {
        cout << endl << "Error: No puedes seguirte a ti mismo." << endl;
        return;
    }
    if (usuarioSeguido->obtenerPremium() == 0) {
        cout << endl << "Error: Solo puedes seguir playlists de usuarios premium." << endl;
        return;
    }

    usuario->ponerUsuarioSeguido(usuarioASeguir);
    guardarEnArchivo();
    cout << endl << "Ahora estas siguiendo a: " << usuarioASeguir << endl;
}

void LecturaUsuario::dejarDeSeguir(string nombreUsuario) {
    Usuario* usuario = obtenerUsuario(nombreUsuario);
    if (usuario == nullptr) {
        cout << endl << "Error: No se encontro al usuario " << nombreUsuario << endl;
        return;
    }

string seguido = usuario->obtenerUsuarioSeguido();

    if (!seguido.empty()) {
        cout << endl << "Has dejado de seguir a: " << seguido << endl;
        usuario->ponerUsuarioSeguido("");
        guardarEnArchivo();
    } else {
        cout << endl << "Actualmente no estas siguiendo a nadie." << endl;
    }
}
