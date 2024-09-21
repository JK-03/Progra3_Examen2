#include "flota.h"
#include <iostream>

Flota::~Flota() {
    for (auto vehiculo : vehiculos) {
        delete vehiculo;
    }
}

void Flota::agregarVehiculo(Vehiculo* vehiculo) {
    vehiculos.push_back(vehiculo);
}

const std::vector<Vehiculo*>& Flota::obtenerVehiculos() const {
    return vehiculos;
}

void Flota::eliminarVehiculo(size_t index) {
    if (index < vehiculos.size()) {
        delete vehiculos[index];
        vehiculos.erase(vehiculos.begin() + index);
    }
}

void Flota::mostrarFlota() const {
    for (const auto& vehiculo : vehiculos) {
        std::cout << "Modelo: " << vehiculo->obtenerModelo()
                  << ", Mantenimiento: " << vehiculo->calcularMantenimiento() << std::endl;
    }
}
