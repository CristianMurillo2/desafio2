#ifndef ANUNCIO_H
#define ANUNCIO_H

#include <string>

class Anuncio {
private:
    int id;
    std::string texto;
    char categoria;
    int prioridad;

public:
    Anuncio();
    Anuncio(int id, const std::string& texto, char categoria);
    Anuncio(const Anuncio& otro);
    ~Anuncio();

    Anuncio& operator=(const Anuncio& otro);

    int getId() const;
    void setId(int id);

    std::string getTexto() const;
    void setTexto(const std::string& texto);

    char getCategoria() const;
    void setCategoria(char categoria);

    int getPrioridad() const;
    void setPrioridad(int prioridad);

    void mostrar() const;

    static Anuncio* seleccionarAleatorio(Anuncio* lista, int total, int& ultimoMostrado);

    void guardarEnArchivo(const std::string& nombreArchivo) const;
    static Anuncio* cargarDesdeArchivo(const std::string& nombreArchivo, int& totalAnuncios);
};

#endif
