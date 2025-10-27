#include "usuario.h"
#include <stdexcept>
#include "eficiencia.h"

string Usuario::obtenerNombre() const {
    MedidorEficiencia::incrementarIteraciones();
    return nombre;
}
void Usuario::ponerNombre(const string &newNombre) {
    MedidorEficiencia::incrementarIteraciones();
    nombre = newNombre;
}
void Usuario::ponerContrasena(const string &newContrasena) {
    MedidorEficiencia::incrementarIteraciones();
    contrasena = newContrasena;
}
string Usuario::obtenerContrasena() const {
    MedidorEficiencia::incrementarIteraciones();
    return contrasena;
}
int Usuario::obtenerPremium() const {
    MedidorEficiencia::incrementarIteraciones();
    return premium;
}
void Usuario::ponerPremium(int newPremium) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(newPremium));
    premium = newPremium;
}
string Usuario::obtenerNombre() {
    MedidorEficiencia::incrementarIteraciones();
    return nombre;
}
string Usuario::obtenerContrasena() {
    MedidorEficiencia::incrementarIteraciones();
    return contrasena;
}
int Usuario::obtenerPremium() {
    MedidorEficiencia::incrementarIteraciones();
    return premium;
}

Usuario::Usuario() {
    MedidorEficiencia::incrementarIteraciones();
    nombre = "";
    contrasena = "";
    premium = 0;
    usuarioSeguido = "";
}

Usuario::Usuario(string n, string c, int a) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(n));
    MedidorEficiencia::sumarMemoria(n.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(c));
    MedidorEficiencia::sumarMemoria(c.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(a));
    nombre = n;
    contrasena = c;
    premium = a;
    usuarioSeguido = "";
}

void Usuario::ponerDatos(string n, string c, int a) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(n));
    MedidorEficiencia::sumarMemoria(n.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(c));
    MedidorEficiencia::sumarMemoria(c.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(a));
    nombre = n;
    contrasena = c;
    premium = a;
    usuarioSeguido = "";
}

Usuario::Usuario(string n, string c, int a, string seguido) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(n));
    MedidorEficiencia::sumarMemoria(n.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(c));
    MedidorEficiencia::sumarMemoria(c.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(a));
    MedidorEficiencia::sumarMemoria(sizeof(seguido));
    MedidorEficiencia::sumarMemoria(seguido.capacity());
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
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(n));
    MedidorEficiencia::sumarMemoria(n.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(c));
    MedidorEficiencia::sumarMemoria(c.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(a));
    MedidorEficiencia::sumarMemoria(sizeof(seguido));
    MedidorEficiencia::sumarMemoria(seguido.capacity());
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
    MedidorEficiencia::incrementarIteraciones();
    return usuarioSeguido;
}

void Usuario::ponerUsuarioSeguido(const string &newUsuarioSeguido) {
    MedidorEficiencia::incrementarIteraciones();
    if (premium == 1) {
        usuarioSeguido = newUsuarioSeguido;
    } else {
        cout << endl << "Error: Los usuarios estandar no pueden seguir a otros." << endl;
        usuarioSeguido = "";
    }
}

LecturaUsuario::LecturaUsuario() {
    MedidorEficiencia::incrementarIteraciones();
    usuarios = nullptr;
    cantidad = 0;
    nombreArchivo = "";
}

LecturaUsuario::~LecturaUsuario() {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::restarMemoria(cantidad * sizeof(Usuario));
    delete[] usuarios;
}

void LecturaUsuario::cargarDesdeArchivo(const string& nombreArchivo)
{
    MedidorEficiencia::incrementarIteraciones();
    this->nombreArchivo = nombreArchivo;
    MedidorEficiencia::sumarMemoria(this->nombreArchivo.capacity());

    ifstream archivo(nombreArchivo);
    MedidorEficiencia::sumarMemoria(sizeof(archivo));
    if (!archivo.is_open()) {
        cout << endl << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    MedidorEficiencia::sumarMemoria(sizeof(linea));
    int contador = 0;
    MedidorEficiencia::sumarMemoria(sizeof(contador));

    while (getline(archivo, linea)) {
        MedidorEficiencia::incrementarIteraciones();
        if (!linea.empty()) contador++;
    }
    MedidorEficiencia::sumarMemoria(linea.capacity());

    MedidorEficiencia::restarMemoria(cantidad * sizeof(Usuario));
    delete[] usuarios;
    usuarios = new Usuario[contador];
    MedidorEficiencia::sumarMemoria(contador * sizeof(Usuario));
    cantidad = contador;

    archivo.clear();
    archivo.seekg(0);

    int i = 0;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    while (getline(archivo, linea) && i < cantidad) {
        MedidorEficiencia::incrementarIteraciones();
        if (linea.empty()) continue;

        string nombre, contrasena, premiumStr, usuarioSeguido;
        MedidorEficiencia::sumarMemoria(sizeof(nombre));
        MedidorEficiencia::sumarMemoria(sizeof(contrasena));
        MedidorEficiencia::sumarMemoria(sizeof(premiumStr));
        MedidorEficiencia::sumarMemoria(sizeof(usuarioSeguido));
        int premium;
        MedidorEficiencia::sumarMemoria(sizeof(premium));

        size_t pos1 = linea.find(',');
        MedidorEficiencia::sumarMemoria(sizeof(pos1));
        if (pos1 == string::npos) continue;
        nombre = linea.substr(0, pos1);
        MedidorEficiencia::sumarMemoria(nombre.capacity());

        size_t pos2 = linea.find(',', pos1 + 1);
        MedidorEficiencia::sumarMemoria(sizeof(pos2));
        if (pos2 == string::npos) continue;
        contrasena = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        MedidorEficiencia::sumarMemoria(contrasena.capacity());

        size_t pos3 = linea.find(',', pos2 + 1);
        MedidorEficiencia::sumarMemoria(sizeof(pos3));

        try {
            MedidorEficiencia::incrementarIteraciones();
            if (pos3 == string::npos) {
                premiumStr = linea.substr(pos2 + 1);
                MedidorEficiencia::sumarMemoria(premiumStr.capacity());
                premium = stoi(premiumStr);

                usuarios[i].ponerDatos(nombre, contrasena, premium);

            } else {
                premiumStr = linea.substr(pos2 + 1, pos3 - pos2 - 1);
                MedidorEficiencia::sumarMemoria(premiumStr.capacity());
                usuarioSeguido = linea.substr(pos3 + 1);
                MedidorEficiencia::sumarMemoria(usuarioSeguido.capacity());
                premium = stoi(premiumStr);

                usuarios[i].ponerDatos(nombre, contrasena, premium, usuarioSeguido);
            }
            i++;

        } catch (const std::invalid_argument& e) {
            MedidorEficiencia::incrementarIteraciones();
            cout << endl << "Error al convertir premium en linea: " << linea << endl;
        }
    }
    MedidorEficiencia::sumarMemoria(linea.capacity());
    archivo.close();
}

int LecturaUsuario::verificarUsuario(const string* datos){
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(datos));

    string nombreIngresado = datos[0];
    MedidorEficiencia::sumarMemoria(sizeof(nombreIngresado));
    MedidorEficiencia::sumarMemoria(nombreIngresado.capacity());
    string contrasenaIngresada = datos[1];
    MedidorEficiencia::sumarMemoria(sizeof(contrasenaIngresada));
    MedidorEficiencia::sumarMemoria(contrasenaIngresada.capacity());

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < cantidad; i++) {
        MedidorEficiencia::incrementarIteraciones();
        if (usuarios[i].obtenerNombre() == nombreIngresado && usuarios[i].obtenerContrasena() == contrasenaIngresada) {
            return usuarios[i].obtenerPremium();
        }
    }
    cout << endl << "Usuario o contrasena incorrectos." << endl;
    return -1;
}

Usuario* LecturaUsuario::obtenerUsuario(string nombre) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombre));
    MedidorEficiencia::sumarMemoria(nombre.capacity());

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < cantidad; i++) {
        MedidorEficiencia::incrementarIteraciones();
        if (usuarios[i].obtenerNombre() == nombre) {
            return &usuarios[i];
        }
    }
    return nullptr;
}

void LecturaUsuario::guardarEnArchivo() {
    MedidorEficiencia::incrementarIteraciones();
    if (nombreArchivo.empty()) {
        cout << endl << "Error: No se ha cargado ningún archivo." << endl;
        return;
    }

    ofstream archivo(this->nombreArchivo);
    MedidorEficiencia::sumarMemoria(sizeof(archivo));
    if (!archivo.is_open()) {
        cout << endl << "Error: No se pudo abrir el archivo para guardar: " << this->nombreArchivo << endl;
        return;
    }

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < cantidad; i++) {
        MedidorEficiencia::incrementarIteraciones();
        archivo << usuarios[i].obtenerNombre() << ",";
        archivo << usuarios[i].obtenerContrasena() << ",";
        archivo << usuarios[i].obtenerPremium();

        string seguido = usuarios[i].obtenerUsuarioSeguido();
        MedidorEficiencia::sumarMemoria(sizeof(seguido));
        MedidorEficiencia::sumarMemoria(seguido.capacity());

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
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombreUsuario));
    MedidorEficiencia::sumarMemoria(nombreUsuario.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(usuarioASeguir));
    MedidorEficiencia::sumarMemoria(usuarioASeguir.capacity());

    Usuario* usuario = obtenerUsuario(nombreUsuario);
    MedidorEficiencia::sumarMemoria(sizeof(usuario));
    if (usuario == nullptr) {
        cout << endl << "Error: No se encontro al usuario " << nombreUsuario << endl;
        return;
    }

    if (usuario->obtenerPremium() == 0) {
        cout << endl << "Lo sentimos, solo los usuarios premium pueden seguir a otros." << endl;
        return;
    }

    Usuario* usuarioSeguido = obtenerUsuario(usuarioASeguir);
    MedidorEficiencia::sumarMemoria(sizeof(usuarioSeguido));
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
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombreUsuario));
    MedidorEficiencia::sumarMemoria(nombreUsuario.capacity());

    Usuario* usuario = obtenerUsuario(nombreUsuario);
    MedidorEficiencia::sumarMemoria(sizeof(usuario));
    if (usuario == nullptr) {
        cout << endl << "Error: No se encontro al usuario " << nombreUsuario << endl;
        return;
    }

    string seguido = usuario->obtenerUsuarioSeguido();
    MedidorEficiencia::sumarMemoria(sizeof(seguido));
    MedidorEficiencia::sumarMemoria(seguido.capacity());

    if (!seguido.empty()) {
        cout << endl << "Has dejado de seguir a: " << seguido << endl;
        usuario->ponerUsuarioSeguido("");
        guardarEnArchivo();
    } else {
        cout << endl << "Actualmente no estas siguiendo a nadie." << endl;
    }
}
