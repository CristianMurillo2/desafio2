#include "menu.h"

int menuIngreso(){
    int opcion;
    cout << "______________________________" << endl;
    cout << "|   BIENVENIDO A UDEATUNES   |" << endl;
    cout << "______________________________" << endl << endl;
    cout << "1. Ingresar como usuario registrado." << endl;
    cout << "2. Registrarse en la plataforma." << endl;
    cout << "3. Salir de la plataforma." << endl;
    cout << "Selecciona una opcion:";
    while (!(cin >> opcion) || opcion < 1 || opcion > 3) {
        cout << "Entrada invalida. Ingrese un numero entre 1 y 3: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return opcion;
}

string* menuIngresoUsuario(){
    string *registro = new string[2];
    string usuario;
    string contrasena;
    bool usuarioAux = true;
    while(usuarioAux){
        cout << "Ingrese su usuario: ";
        cin >> usuario;
        registro[0] = usuario;
        cout << "Ingrese su contrasena: ";
        cin >> contrasena;
        registro[1] = contrasena;
        cout << endl;

        bool verificacionUsuario = true;
        if(verificacionUsuario == true){
            return registro;

        }
        else{
            registro = nullptr;
            delete[] registro;
        }
    }
}

int menuIngresoPremium(){
    int opcion;
    cout << "1. Reproducir canciones de forma aleatoria." << endl;
    cout << "2. Reproducir cancion especifica." << endl;
    cout << "3. Reproducir mi playlist favorita." << endl;
    cout << "4. Seguir una playlist de otro usuario." << endl;
    cout << "5. Cancelar suscripcion." << endl;
    cout << "6. Salir de la cuenta." << endl;
    cout << "Seleccione una opcion: ";
    while (!(cin >> opcion) || opcion < 1 || opcion > 6) {
        cout << "Entrada invalida. Ingrese un numero entre 1 y 3: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return opcion;
}

int menuFuncionesPremium(){
    int opcion;
    cout << "1. Cancion anterior." << endl;
    cout << "2. Repetir de manera indefinida." << endl;
    cout << "3. Pausar." << endl;
    cout << "4, Cancion siguiente." << endl;
    cout << "5. Agregar cancion a favorito." << endl;
    cout << "6. Volver a menu anterior." << endl;
    cout << "Ingresa una opcion: ";
    while (!(cin >> opcion) || opcion < 1 || opcion > 6) {
        cout << "Entrada invalida. Ingrese un numero entre 1 y 6: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return opcion;
}

int menuFuncionesNoPremium(){
    int opcion;
    cout << "1. Reproducir musica aleatoria." << endl;
    cout << "2. Hacerce Premium." << endl;
    cout << "3. Salir de la cuenta." << endl;
    cout << "Seleccione una opcion:";
    while (!(cin >> opcion) || opcion < 1 || opcion > 3) {
        cout << "Entrada invalida. Ingrese un numero entre 1 y 3: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return opcion;
}

long menuBuscarCancion(){
    long idCancion;
    cout << "Ingrese el ID de la cancion que desea buscar: ";
    while(!(cin >> idCancion)){
        cout << "Entrada invalida. Ingrese un codigo ID valido: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return idCancion;
}
