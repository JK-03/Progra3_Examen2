#ifndef FLOTA_H
#define FLOTA_H

#include <vector>
#include "vehiculo.h"

class Flota {
private:
    std::vector<Vehiculo*> vehiculos;

public:
    ~Flota();
    void agregarVehiculo(Vehiculo* vehiculo);
    void eliminarVehiculo(size_t index);
    const std::vector<Vehiculo*>& obtenerVehiculos() const;
    void mostrarFlota() const;
};

#endif // FLOTA_H
