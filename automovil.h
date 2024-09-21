#ifndef AUTOMOVIL_H
#define AUTOMOVIL_H

#include "vehiculo.h"

class Automovil : public Vehiculo {
public:
    Automovil(const std::string& modelo, int año, float kilometraje);
    double calcularMantenimiento() const override; // Cambiado a double
};

#endif // AUTOMOVIL_H
