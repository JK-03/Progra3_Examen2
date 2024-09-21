#include "EmpleadoFijo.h"

EmpleadoFijo::EmpleadoFijo(const std::string& nombre, int edad, float salario)
    : Empleado(nombre, edad, salario) {}

float EmpleadoFijo::calcularSalario() const {
    return salario;
}
