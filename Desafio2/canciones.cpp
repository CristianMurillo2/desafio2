#include "canciones.h"
#include <iostream>
#include <fstream>
#include <string>

canciones::canciones() {}

canciones::~canciones() {}

string* canciones::buscarCancionPorID(long idBuscado, int esPremium) {

    ifstream archivo("canciones.txt");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo canciones.txt" << endl;
        return nullptr;
    }

    string linea;
    bool encontrado = false;

    string* resultado = new string[4];

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        int pos1 = linea.find(';');
        if (pos1 == string::npos) continue;

        string idEnArchivoStr = linea.substr(0, pos1);
        long idEnArchivoLong = 0;

        try {
            idEnArchivoLong = stoll(idEnArchivoStr);
        } catch (...) {
            continue;
        }

        if (idEnArchivoLong == idBuscado) {
            encontrado = true;

            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);
            int pos4 = linea.find(';', pos3 + 1);

            if (pos2 == string::npos || pos3 == string::npos || pos4 == string::npos) {
                cout << "Error: Linea mal formateada en canciones.txt para ID: " << idBuscado << endl;
                encontrado = false; // Marcamos como no encontrado por formato
                break;
            }

            string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string duracion = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            string ruta128 = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            string ruta320 = linea.substr(pos4 + 1); // El resto de la línea

            resultado[0] = idEnArchivoStr;

            resultado[1] = nombre;

            resultado[2] = duracion;

            if (esPremium == 1) {
                resultado[3] = ruta320;
            } else {
                resultado[3] = ruta128;
            }

            break;
        }
    }

    archivo.close();

    if (encontrado) {
        return resultado;
    } else {
        delete[] resultado;
        cout << "Cancion con ID " << idBuscado << " no encontrada." << endl;
        return nullptr;
    }
}

long canciones::obtenerIdCancionAleatoria() {

    ifstream archivo("canciones.txt");

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir canciones.txt para modo aleatorio." << endl;
        return -1;
    }

    int totalCanciones = 0;
    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.find(';') != string::npos) {
            totalCanciones++;
        }
    }

    if (totalCanciones == 0) {
        cout << "No hay canciones en el archivo." << endl;
        archivo.close();
        return -1;
    }

    long* arregloDeIds = new long[totalCanciones];
    archivo.clear();
    archivo.seekg(0);

    int cancionesCargadas = 0;

    while (getline(archivo, linea) && cancionesCargadas < totalCanciones) {
        if (linea.empty()) continue;

        int pos1 = linea.find(';');
        if (pos1 == string::npos) continue;

        string idStr = linea.substr(0, pos1);

        try {
            arregloDeIds[cancionesCargadas] = stoll(idStr);
            cancionesCargadas++;
        } catch (...) {
        }
    }

    archivo.close();

    if (cancionesCargadas == 0) {
        cout << "Error: No se pudieron cargar IDs validos." << endl;
        delete[] arregloDeIds;
        return -1;
    }

    int indiceAleatorio = rand() % cancionesCargadas;
    long idSeleccionado = arregloDeIds[indiceAleatorio];
    delete[] arregloDeIds;
    return idSeleccionado;
}
