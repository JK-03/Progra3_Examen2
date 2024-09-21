#ifndef EMPLEADOCONTRATADO_H
#define EMPLEADOCONTRATADO_H

#include "Empleado.h"

class EmpleadoContratado : public Empleado {
private:
    float tarifaPorHora;
    int horasTrabajadas;

public:
    EmpleadoContratado(const std::string& nombre, int edad, float tarifaPorHora, int horasTrabajadas);
    float calcularSalario() const override;

    float getTarifaPorHora() const;
    int getHorasTrabajadas() const;
};

#endif // EMPLEADOCONTRATADO_H
