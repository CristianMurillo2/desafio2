#include "menu.h"
#include "usuario.h"
#include "lecturacanciones.h"
#include <cstdlib>
#include <ctime>
#include "lecturaArtistas.h"
#include "cancion.h"
#include "artista.h"
#include "playlist.h"

int main()
{
    srand(time(0));

    LecturaUsuario lector;
    lector.cargarDesdeArchivo("usuarios.txt");

    LecturaArtistas gestorArtistas;
    gestorArtistas.cargarArtistas("artistas.txt");

    LecturaCanciones gestorCanciones;
    gestorCanciones.cargarCanciones("canciones.txt");

    bool ingreso1 = true;
    bool ingreso2 = true;
    int esPremium;
    string usuarioActual;
    string usuarioSeguido;

    while(ingreso1 == true){
        int opcionIngreso;
        opcionIngreso = menuIngreso();
        if(opcionIngreso == 1){
            bool usuValido = true;
            while(usuValido == true){
                string* perfilUsuario = menuIngresoUsuario();
                esPremium = lector.verificarUsuario(perfilUsuario);
                if(esPremium == 1 || esPremium == 0){
                    usuarioActual = perfilUsuario[0];
                    usuValido = false;
                }
                delete[] perfilUsuario;
                perfilUsuario = nullptr;
            }

            if(esPremium == 1){
                Usuario* pUsuarioLogueado = lector.obtenerUsuario(usuarioActual);
                while(ingreso2 == true){
                    cout << endl << endl << "--- ERES USUARIO PREMIUM ---" << endl << endl;
                    int opcionUsuPremium = menuIngresoPremium();

                    if(opcionUsuPremium == 1){ // Reproduccion aleatoria
                        Cancion* cancionAleatoria = gestorCanciones.obtenerCancionAleatoria();
                        if (cancionAleatoria != nullptr) {
                            cout << endl << "--- Reproduciendo Aleatoriamente ---" << endl;
                            cout << "ID: " << cancionAleatoria->obtenerID() << endl;
                            cout << "Nombre: " << cancionAleatoria->obtenerNombre() << endl;
                            cout << "Duracion: " << cancionAleatoria->obtenerDuracion() << endl;
                            cout << "Ruta Audio: " << cancionAleatoria->obtenerRutaAudio(esPremium) << endl;

                            long idArtistaBuscado = cancionAleatoria->obtenerID() / 10000;
                            Artista* artista = gestorArtistas.buscarArtistaPorID(idArtistaBuscado);
                            if (artista != nullptr) {
                                cout << endl << "Artista: " << artista->obtenerNombre() << endl << endl;
                            }
                        }
                        int opcionReproPremium = menuFuncionesPremium();



                    }
                    else if(opcionUsuPremium == 2){ // Reproduccion por busqueda
                        long idCancion = menuBuscarCancion();
                        Cancion* cancionBuscada = gestorCanciones.buscarCancionPorID(idCancion);

                        if (cancionBuscada != nullptr) {
                            cout << "--- Reproduciendo ---" << endl;
                            cout << "ID: " << cancionBuscada->obtenerID() << endl;
                            cout << "Nombre: " << cancionBuscada->obtenerNombre() << endl;
                            cout << "Duracion: " << cancionBuscada->obtenerDuracion() << endl;
                            cout << "Ruta Audio: " << cancionBuscada->obtenerRutaAudio(esPremium) << endl;
                            long idArtistaBuscado = cancionBuscada->obtenerID() / 10000;
                            Artista* artista = gestorArtistas.buscarArtistaPorID(idArtistaBuscado);
                            if (artista != nullptr) {
                                cout << endl << "Artista: " << artista->obtenerNombre() << endl << endl;
                            }
                            system("pause");
                        }
                    }

                    else if(opcionUsuPremium == 3){ //Reproduccion de playlist
                        bool opcionReproPlaylist = true;
                        while(opcionReproPlaylist == true){
                            int opcionReproPlay = menuReproductorPlaylist();
                            if(opcionReproPlay == 1){
                                //Reproduccion aleatoria
                                Cancion* cancionAleatoria = gestorCanciones.obtenerCancionAleatoria();


                            }
                            else if(opcionReproPlay == 2){//Reproduce playlist en orden
                                string archivoPlaylist = usuarioActual + ".txt";
                                Playlist miPlaylist = Playlist::cargarDesdeArchivo(archivoPlaylist, 100);

                                string nombreSeguido = pUsuarioLogueado->obtenerUsuarioSeguido();
                                Playlist playlistSeguida;
                                if (!nombreSeguido.empty()) {
                                    playlistSeguida = Playlist::cargarDesdeArchivo(nombreSeguido + ".txt", 100);
                                }

                                Playlist playlistCombinada("Cola de Reproduccion", 200);

                                for (int i = 0; i < miPlaylist.getNumCanciones(); i++) {
                                    playlistCombinada.agregarCancion(miPlaylist.getCancionID(i));
                                }

                                if (!nombreSeguido.empty()) {
                                    for (int i = 0; i < playlistSeguida.getNumCanciones(); i++) {
                                        playlistCombinada.agregarCancion(playlistSeguida.getCancionID(i));
                                    }
                                }

                                if (playlistCombinada.getNumCanciones() == 0) {
                                    cout << "No se pudo cargar tu playlist o está vacía." << endl;
                                } else {
                                    cout << "¡Iniciando cola de reproducción (Mi Playlist + Playlist Seguida)!" << endl;

                                    int opcionPlaylist = 0;
                                    Cancion cancionActual = playlistCombinada.reproducirActual(esPremium, gestorCanciones);

                                    do {
                                        if (cancionActual.obtenerID() != 0) {
                                            cout << "\n--- Reproduciendo (Cola) ---" << endl;
                                            cout << "Titulo: " << cancionActual.obtenerNombre() << endl;
                                            cout << "Duracion: " << cancionActual.obtenerDuracion() << endl;
                                            cout << "Ruta: " << cancionActual.obtenerRutaAudio(esPremium) << endl;

                                            long idArtistaBuscado = cancionActual.obtenerID() / 10000;
                                            Artista* artista = gestorArtistas.buscarArtistaPorID(idArtistaBuscado);
                                            if (artista != nullptr) {
                                                cout << "Artista: " << artista->obtenerNombre() << endl;
                                            }
                                            cout << "----------------------" << endl;

                                        } else {
                                            cout << "No se pudo encontrar la cancion." << endl;
                                        }

                                        cout << "\n1. Siguiente cancion" << endl;
                                        cout << "2. Cancion anterior" << endl;
                                        cout << "3. Salir de la playlist" << endl;
                                        cout << "Opcion: ";
                                        cin >> opcionPlaylist;

                                        switch(opcionPlaylist) {
                                        case 1:
                                            cancionActual = playlistCombinada.siguiente(esPremium, gestorCanciones);
                                            break;
                                        case 2:
                                            cancionActual = playlistCombinada.anterior(esPremium, gestorCanciones);
                                            break;
                                        case 3:
                                            cout << "Saliendo de la playlist..." << endl;
                                            break;
                                        default:
                                            cout << "Opcion invalida." << endl;
                                        }

                                    } while (opcionPlaylist != 3);
                                }
                            }
                            else if(opcionReproPlay == 3){
                                cout << "Volviendo al menu anterior..." << endl;
                                opcionReproPlaylist = false;
                            }
                        }
                    }
                    else if(opcionUsuPremium == 4){
                        int opcionGestion = menuEditarPlaylist();
                        if (opcionGestion == 1 || opcionGestion == 2) {

                            string archivoPlaylist = usuarioActual + ".txt";
                            Playlist miPlaylist = Playlist::cargarDesdeArchivo(archivoPlaylist, 100);

                            long idCancion = menuBuscarCancion();

                            if (opcionGestion == 1) {
                                Cancion* cancionPtr = gestorCanciones.buscarCancionPorID(idCancion);
                                if (cancionPtr == nullptr) {
                                    cout << "Error: La cancion con ID " << idCancion << " no existe." << endl;
                                } else {
                                    if (miPlaylist.agregarCancion(idCancion)) {
                                        cout << "Exito: Cancion '" << cancionPtr->obtenerNombre() << "' agregada a tu playlist." << endl;
                                        miPlaylist.guardarEnArchivo(archivoPlaylist);
                                    } else {
                                        cout << "Error: No se pudo agregar la cancion (Cancion ya existente o playlist llena)." << endl;
                                    }
                                }
                            }
                            else if (opcionGestion == 2) {
                                if (miPlaylist.eliminarCancion(idCancion)) {
                                    cout << "Exito: Cancion con ID " << idCancion << " eliminada de tu playlist." << endl;
                                    miPlaylist.guardarEnArchivo(archivoPlaylist);
                                } else {
                                    cout << "Error: La cancion con ID " << idCancion << " no se encontraba en tu playlist." << endl;
                                }
                            }
                        }
                        else if (opcionGestion == 3) {
                            cout << "Ingrese el nombre del usuario a seguir: ";
                            string userASeguir;
                            cin >> userASeguir;
                            lector.seguirUsuario(usuarioActual, userASeguir);
                        }
                        else if (opcionGestion == 4) {
                            lector.dejarDeSeguir(usuarioActual);
                        }
                        else if (opcionGestion != 5) {
                            cout << "Opcion no valida." << endl;
                        }
                    }
                    else if(opcionUsuPremium == 5){ // Opcion siendo desarrollada no aplica
                        cout << "Esta opcion esta siendo desarrollada y estara disponible muy pronto." << endl;
                    }
                    else if(opcionUsuPremium == 6){ // Volviendo al menu
                        cout << "Volviendo al menu anterior..." << endl;
                        ingreso2 = false;
                    }
                }
            }


            else if (esPremium == 0){
                while(ingreso2 == true){
                    cout << endl << endl << "--- ERES USUARIO ESTANDAR ---" << endl << endl;
                    int opcionUsuNoPremium = menuFuncionesNoPremium();
                    if(opcionUsuNoPremium == 1){
                        Cancion* cancionAleatoria = gestorCanciones.obtenerCancionAleatoria();
                        if (cancionAleatoria != nullptr) {
                            cout << endl << "--- Reproduciendo Aleatoriamente ---" << endl;
                            cout << "ID: " << cancionAleatoria->obtenerID() << endl;
                            cout << "Nombre: " << cancionAleatoria->obtenerNombre() << endl;
                            cout << "Duracion: " << cancionAleatoria->obtenerDuracion() << endl;
                            cout << "Ruta Audio: " << cancionAleatoria->obtenerRutaAudio(esPremium) << endl;

                            long idArtistaBuscado = cancionAleatoria->obtenerID() / 10000;
                            Artista* artista = gestorArtistas.buscarArtistaPorID(idArtistaBuscado);
                            if (artista != nullptr) {
                                cout << "Artista: " << artista->obtenerNombre() << endl << endl;
                            }


                            // Aquí va la lógica de mostrar anuncio cada 2 canciones.


                            cout << "Reproduciendo... (presiona una tecla para continuar)" << endl;
                            system("pause");
                        }
                    }
                    else if(opcionUsuNoPremium == 2){
                        cout << endl << "Esta opcion esta siendo desarrollada y estara disponible muy pronto." << endl << endl;
                    }
                    else if(opcionUsuNoPremium == 3){
                        cout << "Volviendo al menu anterior..." << endl;
                        ingreso2 = false;
                    }
                }
            }
        }

        else if(opcionIngreso == 2){
            cout << endl <<"Esta opcion esta siendo desarrollada y estara disponible muy pronto." << endl;
        }
        else if(opcionIngreso == 3){
            cout << endl << "Saliendo del programa..." << endl;
            ingreso1 = false;
        }
    }

    cout << "Gracias por usar UdeATunes." << endl;
    system("pause");
    return 0;
}
