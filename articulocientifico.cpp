#include "ArticuloCientifico.h"

ArticuloCientifico::ArticuloCientifico(const std::string& titulo, const std::string& autor, int anioPublicacion, bool disponible, int indiceImpacto)
    : Publicacion(titulo, autor, anioPublicacion, disponible), indiceImpacto(indiceImpacto) {}

int ArticuloCientifico::getIndiceImpacto() const {
    return indiceImpacto;
}

std::string ArticuloCientifico::getInformacion() const {
    return "Título: " + getTitulo() + "\n" +
           "Autor: " + getAutor() + "\n" +
           "Año de Publicación: " + std::to_string(getAnioPublicacion()) + "\n" +
           "Disponible: " + (isDisponible() ? "Sí" : "No") + "\n" +
           "Índice de Impacto: " + std::to_string(indiceImpacto);
}
