#include "EmpleadoContratado.h"

EmpleadoContratado::EmpleadoContratado(const std::string& nombre, int edad, float tarifaPorHora, int horasTrabajadas)
    : Empleado(nombre, edad, tarifaPorHora), tarifaPorHora(tarifaPorHora), horasTrabajadas(horasTrabajadas) {}

float EmpleadoContratado::calcularSalario() const {
    return tarifaPorHora * horasTrabajadas;
}

float EmpleadoContratado::getTarifaPorHora() const {
    return tarifaPorHora;
}

int EmpleadoContratado::getHorasTrabajadas() const {
    return horasTrabajadas;
}
