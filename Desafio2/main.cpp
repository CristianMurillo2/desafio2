#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "lecturaArtistas.h"
#include "cancion.h"
#include "artista.h"
#include "playlist.h"
#include "anuncio.h"
#include "usuario.h"
#include "menu.h"
#include "lecturacanciones.h"
#include "album.h"
#include "eficiencia.h"

void mostrarMetricasActuales(const string& etapa) {
    long long iteraciones = MedidorEficiencia::getIteraciones();
    long long memoria = MedidorEficiencia::getMemoriaAprox();

    cout << endl << ">>> METRICAS ACUMULADAS TRAS [" << etapa << "] <<<" << endl;
    cout << "    Iteraciones Totales: " << iteraciones << endl;
    cout << "    Memoria Total (Aprox): " << memoria << " bytes (" << (memoria / 1024.0 / 1024.0) << " MB)" << endl;
    cout << ">>> -------------------------------------------------- <<<\n" << endl;
}


int main()
{
    MedidorEficiencia::iniciarMedicion();

    srand(time(0));

    LecturaUsuario lector;
    lector.cargarDesdeArchivo("usuarios.txt");

    LecturaArtistas gestorArtistas;
    gestorArtistas.cargarArtistas("artistas.txt");

    LecturaCanciones gestorCanciones;
    gestorCanciones.cargarCanciones("canciones.txt");


    Anuncio* gestorAnuncios = nullptr;
    int totalAnuncios = 0;
    int ultimoAnuncioMostrado = -1;
    gestorAnuncios = Anuncio::cargarDesdeArchivo("anuncios.txt", totalAnuncios);
    if (totalAnuncios == 0) {
        cout << "Advertencia: No se pudo cargar 'anuncios.txt'. No se mostraran anuncios." << endl;
    }

    Album* gestorAlbumes = nullptr;
    int totalAlbumes = 0;
    gestorAlbumes = Album::cargarAlbumes("albumes.txt", totalAlbumes);
    mostrarMetricasActuales("Cargar Canciones, Cargar Artistas, Cargar Usuarios, Cargar Anuncios y Cargar Albumes");
    if (totalAlbumes == 0) {
        cout << "Advertencia: No se pudo cargar 'albumes.txt'. No se mostrará info de álbum." << endl;
    }

    bool ingreso1 = true;
    bool ingreso2 = true;
    int esPremium;
    string usuarioActual;
    string usuarioSeguido;
    long ultimoIdAleatorio = 0;

    while(ingreso1 == true){
        int opcionIngreso;
        opcionIngreso = menuIngreso();

        if(opcionIngreso == 1){
            ingreso2 = true;
            bool usuValido = true;
            while(usuValido == true){
                string* perfilUsuario = menuIngresoUsuario();

                esPremium = lector.verificarUsuario(perfilUsuario);

                if(esPremium == 1 || esPremium == 0){
                    usuarioActual = perfilUsuario[0];
                    usuValido = false;
                }
                perfilUsuario = nullptr;
                delete[] perfilUsuario;
            }

            if(esPremium == 1){
                Usuario* pUsuarioLogueado = lector.obtenerUsuario(usuarioActual);

                while(ingreso2 == true){
                    cout << endl << endl << "--- ERES USUARIO PREMIUM ---" << endl << endl;
                    int opcionUsuPremium = menuIngresoPremium();

                    if(opcionUsuPremium == 1){
                        int opcionReproduccion = menuFuncionesPremium();

                        if (opcionReproduccion == 1) {
                            string archivoPlaylist = usuarioActual + ".txt";
                            Playlist miPlaylist = Playlist::cargarDesdeArchivo(archivoPlaylist, 100);

                            string nombreSeguido = pUsuarioLogueado->obtenerUsuarioSeguido();
                            Playlist playlistSeguida;
                            if (!nombreSeguido.empty()) {
                                playlistSeguida = Playlist::cargarDesdeArchivo(nombreSeguido + ".txt", 100);
                            }

                            Playlist playlistCombinada("Playlist de Reproduccion", 200);
                            for (int i = 0; i < miPlaylist.getNumCanciones(); i++) {
                                playlistCombinada.agregarCancion(miPlaylist.getCancionID(i));
                            }
                            if (!nombreSeguido.empty()) {
                                for (int i = 0; i < playlistSeguida.getNumCanciones(); i++) {
                                    playlistCombinada.agregarCancion(playlistSeguida.getCancionID(i));
                                }
                            }
                            mostrarMetricasActuales("Playlists Cargadas");

                            if (playlistCombinada.getNumCanciones() == 0) {
                                cout << "No se pudo cargar tu playlist o está vacía." << endl;
                            } else {
                                cout << "---Iniciando playlist de reproducción (Mi Playlist + Playlist Seguida)---" << endl;
                                int opcionPlaylist = 0;
                                Cancion cancionActual = playlistCombinada.reproducirActual(esPremium, gestorCanciones);
                                mostrarMetricasActuales("Reproducir Primera Cancion");

                                do {
                                    if (cancionActual.obtenerID() != 0) {
                                        cout << endl << "--- Reproduciendo (Playlist) ---" << endl;
                                        long idCancionCompleto = cancionActual.obtenerID();
                                        long idArtistaBuscado = idCancionCompleto / 10000;
                                        long idAlbumBuscado = (idCancionCompleto / 100) % 100;
                                        Album* albumEncontrado = Album::buscarAlbumPorIDs(gestorAlbumes, totalAlbumes, idArtistaBuscado, idAlbumBuscado);
                                        if (albumEncontrado != nullptr) {
                                            cout << endl << "Album: " << albumEncontrado->getNombre() << endl;
                                            cout << "Portada: " << albumEncontrado->getPortada() << endl;
                                        } else {
                                            cout << "Album: (Información no disponible)" << endl;
                                        }
                                        cout << "Titulo: " << cancionActual.obtenerNombre() << endl;
                                        cout << "Duracion: " << cancionActual.obtenerDuracion() << endl;
                                        cout << "Ruta: " << cancionActual.obtenerRutaAudio(esPremium) << endl;
                                        Artista* artista = gestorArtistas.buscarArtistaPorID(idArtistaBuscado);
                                        if (artista != nullptr) {
                                            cout << "Artista: " << artista->obtenerNombre() << endl;
                                        }
                                        cout << "----------------------" << endl;
                                    } else {
                                        cout << "No se pudo encontrar la cancion." << endl;
                                    }

                                    opcionPlaylist = menuControlesRepro();
                                    mostrarMetricasActuales("Menu Controles Repro");

                                    switch(opcionPlaylist) {
                                    case 1:
                                        cancionActual = playlistCombinada.siguiente(esPremium, gestorCanciones);
                                        mostrarMetricasActuales("Siguiente Cancion");
                                        break;
                                    case 2:
                                        cancionActual = playlistCombinada.anterior(esPremium, gestorCanciones);
                                        mostrarMetricasActuales("Cancion Anterior");
                                        break;
                                    case 3:
                                        cout << "Saliendo de la playlist..." << endl;
                                        break;
                                    default:
                                        cout << "Opcion invalida." << endl;
                                    }
                                } while (opcionPlaylist != 3);
                                mostrarMetricasActuales("Salir Reproduccion Playlist");
                            }
                        }
                        else if (opcionReproduccion == 2) {
                            char continuarAleatoria;
                            do {
                                cout << endl << "Iniciando reproduccion aleatoria (5 canciones)..." << endl;
                                for (int i = 0; i < 5; i++) {
                                    Cancion* cancionAleatoria = nullptr;
                                    do {
                                        cancionAleatoria = gestorCanciones.obtenerCancionAleatoria();
                                        if (cancionAleatoria == nullptr) break;
                                    } while (cancionAleatoria->obtenerID() == ultimoIdAleatorio);

                                    if (cancionAleatoria == nullptr) {
                                        cout << "No hay canciones para reproducir." << endl;
                                        break;
                                    }
                                    ultimoIdAleatorio = cancionAleatoria->obtenerID();

                                    cout << endl << "--- Cancion " << (i + 1) << "/5 ---" << endl;
                                    long idCancionCompleto = cancionAleatoria->obtenerID();
                                    long idArtistaBuscado = idCancionCompleto / 10000;
                                    long idAlbumBuscado = (idCancionCompleto / 100) % 100;
                                    Album* albumEncontrado = Album::buscarAlbumPorIDs(gestorAlbumes, totalAlbumes, idArtistaBuscado, idAlbumBuscado);
                                    if (albumEncontrado != nullptr) {
                                        cout << endl << "Album: " << albumEncontrado->getNombre() << endl;
                                        cout << "Portada: " << albumEncontrado->getPortada() << endl;
                                    } else {
                                        cout << "Album: (Información no disponible)" << endl;
                                    }
                                    cout << "Titulo: " << cancionAleatoria->obtenerNombre() << endl;
                                    Artista* artista = gestorArtistas.buscarArtistaPorID(idArtistaBuscado);
                                    if (artista != nullptr) {
                                        cout << "Artista: " << artista->obtenerNombre() << endl;
                                    }
                                    cout << "Duracion: " << cancionAleatoria->obtenerDuracion() << endl;
                                    cout << "Ruta: " << cancionAleatoria->obtenerRutaAudio(esPremium) << endl;
                                    cout << "Reproduciendo por 3 segundos..." << endl;

                                    this_thread::sleep_for(chrono::seconds(3));
                                }
                                cout << endl << "Fin de la tanda aleatoria." << endl;
                                cout << "¿Desea escuchar otra tanda de 5 canciones? (s/n): ";
                                cin >> continuarAleatoria;
                            } while (continuarAleatoria == 's' || continuarAleatoria == 'S');
                            cout << "Volviendo al menu..." << endl << endl;
                        }
                        else if (opcionReproduccion == 3) {
                            string archivoPlaylist = usuarioActual + ".txt";
                            Playlist miPlaylist = Playlist::cargarDesdeArchivo(archivoPlaylist, 100);
                            string nombreSeguido = pUsuarioLogueado->obtenerUsuarioSeguido();
                            Playlist playlistSeguida;
                            if (!nombreSeguido.empty()) {
                                playlistSeguida = Playlist::cargarDesdeArchivo(nombreSeguido + ".txt", 100);
                            }
                            Playlist playlistCombinada("Playlist de Reproduccion", 200);
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
                                cout << "---Iniciando playlist de reproducción (Aleatoria)---" << endl;
                                int opcionPlaylist = 0;
                                Cancion cancionActual = playlistCombinada.reproducirAleatoria(esPremium, gestorCanciones);
                                mostrarMetricasActuales("Reproducir Primera Cancion (Aleatorio)");

                                do {
                                    if (cancionActual.obtenerID() != 0) {
                                        cout << endl << "--- Reproduciendo (Playlist Aleatoria) ---" << endl;
                                        long idCancionCompleto = cancionActual.obtenerID();
                                        long idArtistaBuscado = idCancionCompleto / 10000;
                                        long idAlbumBuscado = (idCancionCompleto / 100) % 100;
                                        Album* albumEncontrado = Album::buscarAlbumPorIDs(gestorAlbumes, totalAlbumes, idArtistaBuscado, idAlbumBuscado);
                                        if (albumEncontrado != nullptr) {
                                            cout << endl << "Album: " << albumEncontrado->getNombre() << endl;
                                            cout << "Portada: " << albumEncontrado->getPortada() << endl;
                                        } else {
                                            cout << "Album: (Información no disponible)" << endl;
                                        }
                                        cout << "Titulo: " << cancionActual.obtenerNombre() << endl;
                                        cout << "Duracion: " << cancionActual.obtenerDuracion() << endl;
                                        cout << "Ruta: " << cancionActual.obtenerRutaAudio(esPremium) << endl;
                                        Artista* artista = gestorArtistas.buscarArtistaPorID(idArtistaBuscado);
                                        if (artista != nullptr) {
                                            cout << "Artista: " << artista->obtenerNombre() << endl;
                                        }
                                        cout << "----------------------" << endl;
                                    } else {
                                        cout << "No se pudo encontrar la cancion." << endl;
                                    }

                                    opcionPlaylist = menuControlesRepro();

                                    switch(opcionPlaylist) {
                                    case 1:
                                        cancionActual = playlistCombinada.reproducirAleatoria(esPremium, gestorCanciones);
                                        mostrarMetricasActuales("Siguiente Cancion");
                                        break;
                                    case 2:
                                        cancionActual = playlistCombinada.anterior(esPremium, gestorCanciones);
                                        mostrarMetricasActuales("Cancion Anterior");
                                        break;
                                    case 3:
                                        cout << endl << "Saliendo de la playlist..." << endl;
                                        break;
                                    default:
                                        cout << "Opcion invalida." << endl;
                                    }
                                } while (opcionPlaylist != 3);
                                mostrarMetricasActuales("Saliendo De Reproduccion.");
                            }
                        }
                    }
                    else if(opcionUsuPremium == 2){
                        char seguirRepro;
                        do{
                            long idCancion = menuBuscarCancion();
                            Cancion* cancionBuscada = gestorCanciones.buscarCancionPorID(idCancion);

                            if (cancionBuscada != nullptr) {
                                cout << "--- Reproduciendo ---" << endl;
                                long idCancionCompleto = cancionBuscada->obtenerID();
                                long idArtistaBuscado = idCancionCompleto / 10000;
                                long idAlbumBuscado = (idCancionCompleto / 100) % 100;
                                Album* albumEncontrado = Album::buscarAlbumPorIDs(gestorAlbumes, totalAlbumes, idArtistaBuscado, idAlbumBuscado);
                                if (albumEncontrado != nullptr) {
                                    cout << endl << "Album: " << albumEncontrado->getNombre() << endl;
                                    cout << "Portada: " << albumEncontrado->getPortada() << endl;
                                } else {
                                    cout << "Album: (Información no disponible)" << endl;
                                }
                                cout << "ID: " << cancionBuscada->obtenerID() << endl;
                                cout << "Nombre: " << cancionBuscada->obtenerNombre() << endl;
                                cout << "Duracion: " << cancionBuscada->obtenerDuracion() << endl;
                                cout << "Ruta Audio: " << cancionBuscada->obtenerRutaAudio(esPremium) << endl;
                                Artista* artista = gestorArtistas.buscarArtistaPorID(idArtistaBuscado);
                                if (artista != nullptr) {
                                    cout << endl << "Artista: " << artista->obtenerNombre() << endl << endl;
                                }
                            }
                            cout << endl << "¿Desea reproducir otra cancion por busqueda? (s/n): ";
                            cin >> seguirRepro;
                        } while (seguirRepro == 's' || seguirRepro == 'S');
                        cout <<  endl <<"Volviendo al menu..." << endl << endl;
                        mostrarMetricasActuales("Final De Reproduccion Por Busqueda");
                    }
                    else if(opcionUsuPremium == 3){
                        int opcionGestion = menuEditarPlaylist();

                        if (opcionGestion == 1 || opcionGestion == 2) {
                            string archivoPlaylist = usuarioActual + ".txt";
                            Playlist miPlaylist = Playlist::cargarDesdeArchivo(archivoPlaylist, 100);

                            long idCancion = menuBuscarCancion();

                            if (opcionGestion == 1) {
                                Cancion* cancionPtr = gestorCanciones.buscarCancionPorID(idCancion);
                                if (cancionPtr == nullptr) {
                                    cout << endl << "Error: La cancion con ID " << idCancion << " no existe." << endl;
                                } else {
                                    if (miPlaylist.agregarCancion(idCancion)) {
                                        cout << endl << "Exito: Cancion '" << cancionPtr->obtenerNombre() << "' agregada a tu playlist." << endl;
                                        miPlaylist.guardarEnArchivo(archivoPlaylist);
                                        mostrarMetricasActuales("Cancion Guardada");
                                    } else {
                                        cout << endl << "Error: No se pudo agregar la cancion (Cancion ya existente o playlist llena)." << endl;
                                    }
                                }
                            }
                            else if (opcionGestion == 2) {
                                if (miPlaylist.eliminarCancion(idCancion)) {
                                    cout << "Exito: Cancion con ID " << idCancion << " eliminada de tu playlist." << endl;
                                    miPlaylist.guardarEnArchivo(archivoPlaylist);
                                    mostrarMetricasActuales("Cancion Eliminada");
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
                            mostrarMetricasActuales("Seguir Usuario");
                        }
                        else if (opcionGestion == 4) {
                            lector.dejarDeSeguir(usuarioActual);
                            mostrarMetricasActuales("Dejar de Seguir Usuario");
                        }
                        else if (opcionGestion != 5) {
                            cout << "Opcion no valida." << endl;
                        }
                    }
                    else if(opcionUsuPremium == 4){
                        cout << endl << "Esta opcion esta siendo desarrollada y estara disponible muy pronto." << endl;
                    }
                    else if(opcionUsuPremium == 5){
                        cout << endl << "Volviendo al menu anterior..." << endl;
                        ingreso2 = false;
                        mostrarMetricasActuales("Cerrar Sesion (Premium)");
                    }
                }
            }
            else if (esPremium == 0){
                while(ingreso2 == true){
                    cout << endl << endl << "--- ERES USUARIO ESTANDAR ---" << endl << endl;
                    int opcionUsuNoPremium = menuFuncionesNoPremium();

                    if(opcionUsuNoPremium == 1){
                        char continuarAleatoria;
                        do {
                            cout << "Iniciando reproduccion aleatoria (5 canciones)..." << endl;
                            for (int i = 0; i < 5; i++) {
                                Cancion* cancionAleatoria = nullptr;
                                do {
                                    cancionAleatoria = gestorCanciones.obtenerCancionAleatoria();
                                    if (cancionAleatoria == nullptr) break;
                                } while (cancionAleatoria->obtenerID() == ultimoIdAleatorio);

                                if (cancionAleatoria == nullptr) {
                                    cout << "No hay canciones para reproducir." << endl;
                                    break;
                                }
                                ultimoIdAleatorio = cancionAleatoria->obtenerID();

                                cout << endl << "--- Cancion " << (i + 1) << "/5 ---" << endl;
                                long idCancionCompleto = cancionAleatoria->obtenerID();
                                long idArtistaBuscado = idCancionCompleto / 10000;
                                long idAlbumBuscado = (idCancionCompleto / 100) % 100;
                                Album* albumEncontrado = Album::buscarAlbumPorIDs(gestorAlbumes, totalAlbumes, idArtistaBuscado, idAlbumBuscado);
                                if (albumEncontrado != nullptr) {
                                    cout << endl << "Album: " << albumEncontrado->getNombre() << endl;
                                    cout << "Portada: " << albumEncontrado->getPortada() << endl;
                                } else {
                                    cout << "Album: (Información no disponible)" << endl;
                                }
                                cout << "Titulo: " << cancionAleatoria->obtenerNombre() << endl;
                                cout << "Duracion: " << cancionAleatoria->obtenerDuracion() << endl;
                                cout << "Ruta audio: " << cancionAleatoria->obtenerRutaAudio(esPremium) << endl;
                                Artista* artista = gestorArtistas.buscarArtistaPorID(idArtistaBuscado);
                                if (artista != nullptr) {
                                    cout << "Artista: " << artista->obtenerNombre() << endl;
                                }

                                cout << "Reproduciendo por 3 segundos..." << endl;
                                this_thread::sleep_for(chrono::seconds(3));

                                if ((i + 1) % 2 == 0 && totalAnuncios > 0) {
                                    cout << endl << "--- ANUNCIO ---" << endl;
                                    Anuncio* ad = Anuncio::seleccionarAleatorio(gestorAnuncios, totalAnuncios, ultimoAnuncioMostrado);
                                    if (ad != nullptr) {
                                        cout << "[" << ad->getCategoria() << "] " << ad->getTexto() << endl;
                                        cout << "(Pausa publicitaria de 3 segundos...)" << endl;
                                        this_thread::sleep_for(chrono::seconds(3));
                                    }
                                    cout << "-----------------" << endl << endl;
                                    mostrarMetricasActuales("Mostrar Anuncio");
                                }
                            }
                            cout << "\nFin de la tanda aleatoria." << endl;
                            cout << "¿Desea escuchar otra tanda de 5 canciones? (s/n): ";
                            cin >> continuarAleatoria;
                        } while (continuarAleatoria == 's' || continuarAleatoria == 'S');
                        cout << "Volviendo al menu..." << endl << endl;
                        mostrarMetricasActuales("Final Tanda De canciones");
                    }
                    else if(opcionUsuNoPremium == 2){
                        cout << endl << "Esta opcion esta siendo desarrollada y estara disponible muy pronto." << endl << endl;
                    }
                    else if(opcionUsuNoPremium == 3){
                        cout << "Volviendo al menu anterior..." << endl;
                        ingreso2 = false;
                        mostrarMetricasActuales("Cerrar Sesion (Estandar)");
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

    mostrarMetricasActuales("FINAL  MEMORIA TOTAL USADA");

    system("pause");
    return 0;
}
