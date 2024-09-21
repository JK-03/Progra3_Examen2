#include "camion.h"

Camion::Camion(const std::string& modelo, int año, float kilometraje, float capacidadCarga)
    : Vehiculo(modelo, año, kilometraje), capacidadCarga(capacidadCarga) {}

double Camion::calcularMantenimiento() const {
    return 100.0 + (kilometraje * 0.1);
}
