#include "Anuncio.h"
#include <iostream>
#include <random>

Anuncio::Anuncio() {
    id = 0;
    texto = "Sin texto";
    categoria = 'C';
    prioridad = 1;
}

Anuncio::Anuncio(int id, const std::string& texto, char categoria) {
    this->id = id;
    this->texto = texto;
    this->categoria = categoria;
    switch (categoria) {
    case 'A': case 'a': prioridad = 3; break;
    case 'B': case 'b': prioridad = 2; break;
    default: prioridad = 1; break;
    }
}
Anuncio::Anuncio(const Anuncio& otro) {
    id = otro.id;
    texto = otro.texto;
    categoria = otro.categoria;
    prioridad = otro.prioridad;
}

Anuncio::~Anuncio() {
}

Anuncio& Anuncio::operator=(const Anuncio& otro) {
    if (this != &otro) {
        id = otro.id;
        texto = otro.texto;
        categoria = otro.categoria;
        prioridad = otro.prioridad;
    }
    return *this;
}

int Anuncio::getId() const { return id; }
void Anuncio::setId(int id) { this->id = id; }

std::string Anuncio::getTexto() const { return texto; }
void Anuncio::setTexto(const std::string& texto) { this->texto = texto; }

char Anuncio::getCategoria() const { return categoria; }
void Anuncio::setCategoria(char categoria) {
    this->categoria = categoria;
    switch (categoria) {
    case 'A': case 'a': prioridad = 3; break;
    case 'B': case 'b': prioridad = 2; break;
    default: prioridad = 1; break;
    }
}

int Anuncio::getPrioridad() const { return prioridad; }
void Anuncio::setPrioridad(int prioridad) { this->prioridad = prioridad; }

void Anuncio::mostrar() const {
    std::cout << "\n--- PUBLICIDAD ---\n";
    std::cout << texto << "\n";
    std::cout << "------------------\n\n";
}

Anuncio* Anuncio::seleccionarAleatorio(Anuncio* lista, int total, int& ultimoMostrado) {
    if (total == 0) return nullptr;
        int pesoTotal = 0;
    for (int i = 0; i < total; i++)
        pesoTotal += lista[i].getPrioridad();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, pesoTotal);

    int valor = dist(gen);
    int acumulado = 0;
    int indice = 0;

    for (int i = 0; i < total; i++) {
        acumulado += lista[i].getPrioridad();
        if (valor <= acumulado) {
            indice = i;
            break;
        }
    }

    if (indice == ultimoMostrado && total > 1) {
        indice = (indice + 1) % total;
    }

    ultimoMostrado = indice;
    return &lista[indice];
}
