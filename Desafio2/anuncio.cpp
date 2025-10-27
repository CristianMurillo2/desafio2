#include "anuncio.h"
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include "eficiencia.h"


Anuncio::Anuncio() {
    MedidorEficiencia::incrementarIteraciones();
    id = 0;
    texto = "Sin texto";
    categoria = 'C';
    prioridad = 1;
    MedidorEficiencia::sumarMemoria(sizeof(id));
    MedidorEficiencia::sumarMemoria(sizeof(texto) + texto.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(categoria));
    MedidorEficiencia::sumarMemoria(sizeof(prioridad));
}

Anuncio::Anuncio(int id, const std::string& texto, char categoria) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(id));
    MedidorEficiencia::sumarMemoria(sizeof(texto) + texto.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(categoria));

    this->id = id;
    this->texto = texto;
    this->categoria = categoria;
    switch (categoria) {
    case 'A': case 'a': prioridad = 3; break;
    case 'B': case 'b': prioridad = 2; break;
    default: prioridad = 1; break;
    }
    MedidorEficiencia::sumarMemoria(sizeof(prioridad));
}

Anuncio::Anuncio(const Anuncio& otro) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(otro));
    id = otro.id;
    texto = otro.texto;
    categoria = otro.categoria;
    prioridad = otro.prioridad;
    MedidorEficiencia::sumarMemoria(sizeof(id));
    MedidorEficiencia::sumarMemoria(sizeof(texto) + texto.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(categoria));
    MedidorEficiencia::sumarMemoria(sizeof(prioridad));
}

Anuncio::~Anuncio() {
    MedidorEficiencia::incrementarIteraciones();
}

Anuncio& Anuncio::operator=(const Anuncio& otro) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(otro));
    if (this != &otro) {
        id = otro.id;
        texto = otro.texto;
        categoria = otro.categoria;
        prioridad = otro.prioridad;
    }
    return *this;
}

int Anuncio::getId() const {
    MedidorEficiencia::incrementarIteraciones();
    return id;
}
void Anuncio::setId(int id) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(id));
    this->id = id;
}

std::string Anuncio::getTexto() const {
    MedidorEficiencia::incrementarIteraciones();
    return texto;
}
void Anuncio::setTexto(const std::string& texto) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(texto) + texto.capacity());
    this->texto = texto;
}

char Anuncio::getCategoria() const {
    MedidorEficiencia::incrementarIteraciones();
    return categoria;
}
void Anuncio::setCategoria(char categoria) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(categoria));
    this->categoria = categoria;
    switch (categoria) {
    case 'A': case 'a': prioridad = 3; break;
    case 'B': case 'b': prioridad = 2; break;
    default: prioridad = 1; break;
    }
}

int Anuncio::getPrioridad() const {
    MedidorEficiencia::incrementarIteraciones();
    return prioridad;
}
void Anuncio::setPrioridad(int prioridad) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(prioridad));
    this->prioridad = prioridad;
}

void Anuncio::mostrar() const {
    MedidorEficiencia::incrementarIteraciones();
    std::cout << "\n--- PUBLICIDAD ---\n";
    std::cout << texto << "\n";
    std::cout << "------------------\n\n";
}

Anuncio* Anuncio::seleccionarAleatorio(Anuncio* lista, int total, int& ultimoMostrado) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(lista));
    MedidorEficiencia::sumarMemoria(sizeof(total));
    MedidorEficiencia::sumarMemoria(sizeof(ultimoMostrado));

    if (total == 0) return nullptr;
    int pesoTotal = 0;
    MedidorEficiencia::sumarMemoria(sizeof(pesoTotal));

    int i;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < total; i++){
        MedidorEficiencia::incrementarIteraciones();
        pesoTotal += lista[i].getPrioridad();
    }

    std::random_device rd;
    MedidorEficiencia::sumarMemoria(sizeof(rd));
    std::mt19937 gen(rd());
    MedidorEficiencia::sumarMemoria(sizeof(gen));
    std::uniform_int_distribution<> dist(1, pesoTotal);
    MedidorEficiencia::sumarMemoria(sizeof(dist));

    int valor = dist(gen);
    MedidorEficiencia::sumarMemoria(sizeof(valor));
    int acumulado = 0;
    MedidorEficiencia::sumarMemoria(sizeof(acumulado));
    int indice = 0;
    MedidorEficiencia::sumarMemoria(sizeof(indice));

    MedidorEficiencia::sumarMemoria(sizeof(i));
    for (i = 0; i < total; i++) {
        MedidorEficiencia::incrementarIteraciones();
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

void Anuncio::guardarEnArchivo(const std::string& nombreArchivo) const {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombreArchivo) + nombreArchivo.capacity());
    std::ofstream archivo(nombreArchivo, std::ios::app);
    MedidorEficiencia::sumarMemoria(sizeof(archivo));
    if (!archivo.is_open()) return;
    archivo << id << ';'
            << categoria << ';'
            << prioridad << ';'
            << texto << '\n';
    archivo.close();
}

Anuncio* Anuncio::cargarDesdeArchivo(const std::string& nombreArchivo, int& totalAnuncios) {
    MedidorEficiencia::incrementarIteraciones();
    MedidorEficiencia::sumarMemoria(sizeof(nombreArchivo) + nombreArchivo.capacity());
    MedidorEficiencia::sumarMemoria(sizeof(totalAnuncios));

    std::ifstream archivo(nombreArchivo);
    MedidorEficiencia::sumarMemoria(sizeof(archivo));
    if (!archivo.is_open()) {
        totalAnuncios = 0;
        return nullptr;
    }
    totalAnuncios = 0;
    std::string linea;
    MedidorEficiencia::sumarMemoria(sizeof(linea));

    while (std::getline(archivo, linea)) {
        MedidorEficiencia::incrementarIteraciones();
        if (!linea.empty()) {
            totalAnuncios++;
        }
    }
    MedidorEficiencia::sumarMemoria(linea.capacity());

    if (totalAnuncios == 0) return nullptr;

    archivo.clear();
    archivo.seekg(0);
    Anuncio* lista = new Anuncio[totalAnuncios];
    MedidorEficiencia::sumarMemoria(sizeof(lista));
    MedidorEficiencia::sumarMemoria(totalAnuncios * sizeof(Anuncio));

    int i = 0;
    MedidorEficiencia::sumarMemoria(sizeof(i));
    while (std::getline(archivo, linea)) {
        MedidorEficiencia::incrementarIteraciones();
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        MedidorEficiencia::sumarMemoria(sizeof(ss));
        std::string parte;
        MedidorEficiencia::sumarMemoria(sizeof(parte));
        std::getline(ss, parte, ';');

        try {
            MedidorEficiencia::incrementarIteraciones();
            lista[i].id = std::stoi(parte);
            std::getline(ss, parte, ';');
            lista[i].setCategoria(parte[0]);
            std::getline(ss, parte);
            lista[i].setTexto(parte);
            i++;
        } catch (...) {
            MedidorEficiencia::incrementarIteraciones();
            std::cout << "Error al leer linea de anuncio: " << linea << std::endl;
            totalAnuncios--;
        }
        MedidorEficiencia::sumarMemoria(parte.capacity());
    }
    MedidorEficiencia::sumarMemoria(linea.capacity());
    return lista;
}
