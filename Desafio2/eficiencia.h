#pragma once
#include <string>
#include <iostream>
using namespace std;

class MedidorEficiencia {
public:
    static long long contadorIteraciones;
    static long long contadorMemoriaAprox; // en bytes
    static void iniciarMedicion() {
        contadorIteraciones = 0;
        contadorMemoriaAprox = 0;
    }

    static void incrementarIteraciones(long long cantidad = 1) {
        contadorIteraciones += cantidad;
    }

    static long long getIteraciones() {
        return contadorIteraciones;
    }

    static void sumarMemoria(long long bytesAñadidos) {
        contadorMemoriaAprox += bytesAñadidos;
    }

    static void restarMemoria(long long bytesQuitados) {
        contadorMemoriaAprox -= bytesQuitados;
    }

    static long long getMemoriaAprox() {
        return contadorMemoriaAprox;
    }
};

inline long long MedidorEficiencia::contadorIteraciones = 0;
inline long long MedidorEficiencia::contadorMemoriaAprox = 0;


