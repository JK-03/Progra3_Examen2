#ifndef CAMION_H
#define CAMION_H

#include "vehiculo.h"

class Camion : public Vehiculo {
private:
    float capacidadCarga;

public:
    Camion(const std::string& modelo, int año, float kilometraje, float capacidadCarga);
    double calcularMantenimiento() const override;
};

#endif // CAMION_H
