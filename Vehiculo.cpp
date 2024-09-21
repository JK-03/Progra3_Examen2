#include "vehiculo.h"

Vehiculo::Vehiculo(const std::string& modelo, int año, float kilometraje)
    : modelo(modelo), año(año), kilometraje(kilometraje) {}

Vehiculo::~Vehiculo() {}

std::string Vehiculo::obtenerModelo() const {
    return modelo;
}

int Vehiculo::obtenerAño() const {
    return año;
}

float Vehiculo::obtenerKilometraje() const {
    return kilometraje;
}
