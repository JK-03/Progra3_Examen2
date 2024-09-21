#include "Revista.h"

Revista::Revista(const std::string& titulo, const std::string& autor, int anioPublicacion, bool disponible, int numeroEdicion)
    : Publicacion(titulo, autor, anioPublicacion, disponible), numeroEdicion(numeroEdicion) {}

int Revista::getNumeroEdicion() const {
    return numeroEdicion;
}

std::string Revista::getInformacion() const {
    return "Título: " + getTitulo() + "\n" +
           "Autor: " + getAutor() + "\n" +
           "Año de Publicación: " + std::to_string(getAnioPublicacion()) + "\n" +
           "Disponible: " + (isDisponible() ? "Sí" : "No") + "\n" +
           "Número de Edición: " + std::to_string(numeroEdicion);
}
