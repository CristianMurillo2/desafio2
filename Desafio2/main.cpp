#include "menu.h"
#include "usuario.h"

int main()
{

/// zona lectura de archivos

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
            LecturaUsuario lector;
            lector.cargarDesdeArchivo("usuarios.txt");
            esPremium = lector.verificarUsuario(perfilUsuario);
            if(esPremium == 1 || esPremium == 0){
                usuValido = false;
            }
        }
        if (esPremium == 0 || esPremium == 1) {
            ingreso2 = true;
        }
        if(esPremium == 1){
            while(ingreso2 == true){
                int opcionUsuPremium = menuIngresoPremium();
                if(opcionUsuPremium == 1){
                    cout << "Reproduciendo canciones aleatoria." << endl;
                    int opcionReproPremium = menuFuncionesPremium();
                    //va de 1 a 6 segun lo que se necesite, retroceder,repetir de manera infinita, pausar, cancion siguiente, agregar a favorito,
                }
                else if(opcionUsuPremium == 2){
                    cout << "Lista de canciones." << endl;
                    //Muestra canciones y se toma el numero
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
                int opcionUsuNoPremium = menuFuncionesNoPremium();
                if(opcionUsuNoPremium == 1){
                    cout << "Reproduciendo canciones aleatorias" << endl;
                    //funciones aleatorias
                }
                else if(opcionUsuNoPremium == 2){
                    cout << endl << "Esta opcion esta siendo desarrollada y estara disponible muy pronto." << endl << endl;
                }
                else if(opcionUsuNoPremium == 3){
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



system("pause");
return 0;
}
