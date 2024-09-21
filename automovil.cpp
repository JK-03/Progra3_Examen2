#include "automovil.h"

Automovil::Automovil(const std::string& modelo, int año, float kilometraje)
    : Vehiculo(modelo, año, kilometraje) {}

double Automovil::calcularMantenimiento() const {
    return (kilometraje / 1000) * 50;
}
