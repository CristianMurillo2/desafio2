#include "menu.h"
#include "usuario.h"
#include "lecturacanciones.h" // ¡Genial!
#include <cstdlib>
#include <ctime>
#include "lecturaArtistas.h" // ¡Genial!
#include "cancion.h"
#include "artista.h"

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

    while(ingreso1 == true){
        int opcionIngreso;
        opcionIngreso = menuIngreso();
        if(opcionIngreso == 1){
            bool usuValido = true;
            while(usuValido == true){
                string* perfilUsuario = menuIngresoUsuario();
                esPremium = lector.verificarUsuario(perfilUsuario);
                if(esPremium == 1 || esPremium == 0){
                    usuValido = false;
                }

                delete[] perfilUsuario;
                perfilUsuario = nullptr;
            }

            if (esPremium == 0 || esPremium == 1) {
                ingreso2 = true;
            }

            if(esPremium == 1){
                while(ingreso2 == true){
                    cout << endl << endl << "--- ERES USUARIO PREMIUM ---" << endl << endl;
                    int opcionUsuPremium = menuIngresoPremium();

                    if(opcionUsuPremium == 1){
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
                    else if(opcionUsuPremium == 2){
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
                    else if(opcionUsuPremium == 3){
                        cout << "Reproduciendo playlist favorita" << endl;
                    }
                    else if(opcionUsuPremium == 4){
                        cout << "Siguiendo una playlist de otro usuarios" << endl;
                    }
                    else if(opcionUsuPremium == 5){
                        cout << "Esta opcion esta siendo desarrollada y estara disponible muy pronto." << endl;
                    }
                    else if(opcionUsuPremium == 6){
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
