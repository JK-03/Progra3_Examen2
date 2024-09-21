#ifndef EMPLEADOFIJO_H
#define EMPLEADOFIJO_H

#include "Empleado.h"

class EmpleadoFijo : public Empleado {
public:
    EmpleadoFijo(const std::string& nombre, int edad, float salario);
    float calcularSalario() const override;
};

#endif // EMPLEADOFIJO_H
