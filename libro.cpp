#include "Libro.h"

Libro::Libro(const std::string& titulo, const std::string& autor, int anioPublicacion, bool disponible, int numeroPaginas)
    : Publicacion(titulo, autor, anioPublicacion, disponible), numeroPaginas(numeroPaginas) {}

int Libro::getNumeroPaginas() const {
    return numeroPaginas;
}

std::string Libro::getInformacion() const {
    return "Título: " + getTitulo() + "\n" +
           "Autor: " + getAutor() + "\n" +
           "Año de Publicación: " + std::to_string(getAnioPublicacion()) + "\n" +
           "Disponible: " + (isDisponible() ? "Sí" : "No") + "\n" +
           "Número de Páginas: " + std::to_string(numeroPaginas);
}
