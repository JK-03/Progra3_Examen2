#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>

class Vehiculo {
protected:
    std::string modelo;
    int año;
    float kilometraje;

public:
    Vehiculo(const std::string& modelo, int año, float kilometraje);
    virtual ~Vehiculo() = 0;
    virtual double calcularMantenimiento() const = 0;

    std::string obtenerModelo() const;
    int obtenerAño() const;
    float obtenerKilometraje() const;
};

#endif // VEHICULO_H
