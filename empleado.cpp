#include "Empleado.h"

Empleado::Empleado(const std::string& nombre, int edad, float salario)
    : nombre(nombre), edad(edad), salario(salario) {}

Empleado::~Empleado() = default;

std::string Empleado::getNombre() const { return nombre; }
int Empleado::getEdad() const { return edad; }
float Empleado::getSalario() const { return salario; }
