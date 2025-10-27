#include "menu.h"
#include "eficiencia.h"

    int menuIngreso(){
    MedidorEficiencia::incrementarIteraciones();
    int opcion;
    MedidorEficiencia::sumarMemoria(sizeof(opcion));
    cout << "______________________________" << endl;
    cout << "|    BIENVENIDO A UDEATUNES    |" << endl;
    cout << "______________________________" << endl << endl;
    cout << "1. Ingresar como usuario registrado." << endl;
    cout << "2. Registrarse en la plataforma." << endl;
    cout << "3. Salir de la plataforma." << endl;
    cout << "Selecciona una opcion:";

    while (!(cin >> opcion) || opcion < 1 || opcion > 3) {
        MedidorEficiencia::incrementarIteraciones();
        cout << "Entrada invalida. Ingrese un numero entre 1 y 3: ";
        cin.clear();
        cin.ignore(255, '\n');
    }

    return opcion;
}

string* menuIngresoUsuario(){
    MedidorEficiencia::incrementarIteraciones();

    string *registro = new string[2];
    MedidorEficiencia::sumarMemoria(sizeof(registro));
    MedidorEficiencia::sumarMemoria(2 * sizeof(string));

    string usuario;
    MedidorEficiencia::sumarMemoria(sizeof(usuario));
    string contrasena;
    MedidorEficiencia::sumarMemoria(sizeof(contrasena));
    bool usuarioAux = true;
    MedidorEficiencia::sumarMemoria(sizeof(usuarioAux));

    while(usuarioAux){
        MedidorEficiencia::incrementarIteraciones();

        cout << "Ingrese su usuario: ";
        cin >> usuario;
        MedidorEficiencia::sumarMemoria(usuario.capacity());
        registro[0] = usuario;

        cout << "Ingrese su contrasena: ";
        cin >> contrasena;
        MedidorEficiencia::sumarMemoria(contrasena.capacity());
        registro[1] = contrasena;
        cout << endl;

        bool verificacionUsuario = true;
        MedidorEficiencia::sumarMemoria(sizeof(verificacionUsuario));

        if(verificacionUsuario == true){
            return registro;
        }
        else{
            MedidorEficiencia::restarMemoria(2 * sizeof(string));
            delete[] registro;
            registro = nullptr;
            usuarioAux = false;
        }
    }
    return nullptr;
}

int menuIngresoPremium(){
    MedidorEficiencia::incrementarIteraciones();
    int opcion;
    MedidorEficiencia::sumarMemoria(sizeof(opcion));

    cout << "1. Reproducir canciones." << endl;
    cout << "2. Reproducir cancion especifica." << endl;
    cout << "3. Editar playlist." << endl;
    cout << "4. Cancelar suscripcion." << endl;
    cout << "5. Salir de la cuenta." << endl;
    cout << "Seleccione una opcion: ";

    while (!(cin >> opcion) || opcion < 1 || opcion > 5) {
        MedidorEficiencia::incrementarIteraciones();
        cout << "Entrada invalida. Ingrese un numero entre 1 y 5: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return opcion;
}

int menuFuncionesPremium(){
    MedidorEficiencia::incrementarIteraciones();
    int opcion;
    MedidorEficiencia::sumarMemoria(sizeof(opcion));

    cout << endl << "--- Modo de Reproduccion ---" << endl;
    cout << "1. Reproducir mi playlist (En orden)." << endl;
    cout << "2. Reproduccion aleatoria (Tanda de 5 canciones)." << endl;
    cout << "3. Reproducir mi playlist (Aleatorio)." << endl;
    cout << "4. Volver" << endl;
    cout << "Ingresa una opcion: ";

    while (!(cin >> opcion) || opcion < 1 || opcion > 4) {
        MedidorEficiencia::incrementarIteraciones();
        cout << "Entrada invalida. Ingrese un numero entre 1 y 4: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return opcion;
}

int menuFuncionesNoPremium(){
    MedidorEficiencia::incrementarIteraciones();
    int opcion;
    MedidorEficiencia::sumarMemoria(sizeof(opcion));

    cout << "1. Reproducir musica aleatoria." << endl;
    cout << "2. Hacerce Premium." << endl;
    cout << "3. Salir de la cuenta." << endl;
    cout << "Seleccione una opcion:";

    while (!(cin >> opcion) || opcion < 1 || opcion > 3) {
        MedidorEficiencia::incrementarIteraciones();
        cout << "Entrada invalida. Ingrese un numero entre 1 y 3: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return opcion;
}

long menuBuscarCancion(){
    MedidorEficiencia::incrementarIteraciones();
    long idCancion;
    MedidorEficiencia::sumarMemoria(sizeof(idCancion));

    cout << "Ingrese el ID de la cancion que desea buscar: ";

    while(!(cin >> idCancion)){
        MedidorEficiencia::incrementarIteraciones();
        cout << "Entrada invalida. Ingrese un codigo ID valido: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return idCancion;
}

int menuReproductorPlaylist(){
    MedidorEficiencia::incrementarIteraciones();
    int opcion;
    MedidorEficiencia::sumarMemoria(sizeof(opcion));

    cout << "1. Reproducir aleatoriamente lista de favoritos." << endl;
    cout << "2. Reproducir canciones en orden original." << endl;
    cout << "3. Volver al menu anterior." << endl;
    cout << "Seleccione una opcion: ";

    while (!(cin >> opcion) || opcion < 1 || opcion > 3) {
        MedidorEficiencia::incrementarIteraciones();
        cout << "Entrada invalida. Ingrese un numero entre 1 y 3: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return opcion;
}

int menuEditarPlaylist(){
    MedidorEficiencia::incrementarIteraciones();
    int opcion;
    MedidorEficiencia::sumarMemoria(sizeof(opcion));

    cout << endl << "1. Agregar cancion a playlist." << endl;
    cout << "2. Eliminar cancion de playlist." << endl;
    cout << "3. Seguir una playlist de otro usuario." << endl;
    cout << "4. Dejar de seguir una playlist de otro usuario." << endl;
    cout << "5. Volver al menu anterior." << endl;
    cout << "Selecciona una opcion: ";

    while (!(cin >> opcion) || opcion < 1 || opcion > 5) {
        MedidorEficiencia::incrementarIteraciones();
        cout << "Entrada invalida. Ingrese un numero entre 1 y 5: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return opcion;
}

int menuControlesRepro(){
    MedidorEficiencia::incrementarIteraciones();
    int opcion;
    MedidorEficiencia::sumarMemoria(sizeof(opcion));

    cout << endl <<"1. Siguiente cancion (Aleatoria)" << endl;
    cout << "2. Cancion anterior" << endl;
    cout << "3. Salir de la playlist" << endl;
    cout << "Selecciona una pcion: ";

    while (!(cin >> opcion) || opcion < 1 || opcion > 3) {
        MedidorEficiencia::incrementarIteraciones();
        cout << "Entrada invalida. Ingrese un numero entre 1 y 3: ";
        cin.clear();
        cin.ignore(255, '\n');
    }
    return opcion;
}

void mostrarMetricasActuales(const string& etapa) {
    long long iteraciones = MedidorEficiencia::getIteraciones();
    long long memoria = MedidorEficiencia::getMemoriaAprox();

    cout << endl << ">>> METRICAS ACUMULADAS TRAS [" << etapa << "] <<<" << endl;
    cout << "    Iteraciones Totales: " << iteraciones << endl;
    cout << "    Memoria Total (Aprox): " << memoria << " bytes (" << (memoria / 1024.0 / 1024.0) << " MB)" << endl;
    cout << ">>> -------------------------------------------------- <<<\n" << endl;
}
