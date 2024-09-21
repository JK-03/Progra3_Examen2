#include "Publicacion.h"

Publicacion::Publicacion(const std::string& titulo, const std::string& autor, int anioPublicacion, bool disponible)
    : titulo(titulo), autor(autor), anioPublicacion(anioPublicacion), disponible(disponible) {}

Publicacion::~Publicacion() {}

std::string Publicacion::getTitulo() const { return titulo; }
std::string Publicacion::getAutor() const { return autor; }
int Publicacion::getAnioPublicacion() const { return anioPublicacion; }
bool Publicacion::isDisponible() const { return disponible; }
void Publicacion::setDisponible(bool disponible) { this->disponible = disponible; }
