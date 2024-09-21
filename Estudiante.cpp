#include "Estudiante.h"
#include <cstdlib>
#include <ctime>

std::set<std::string> Estudiante::numerosCuentasGenerados;

Estudiante::Estudiante(const std::string& nombre, int edad)
    : nombre(nombre), edad(edad), numeroCuenta(generarNumeroCuenta()) {
}

Estudiante::~Estudiante() {
}

void Estudiante::agregarMateria(const std::string& nombreMateria, int calificacion) {
    materias.push_back(nombreMateria);
    calificaciones.push_back(calificacion);
}

std::string Estudiante::generarNumeroCuenta() {
    std::string cuenta;
    do {
        cuenta.clear();
        for (int i = 0; i < 8; ++i) {
            cuenta += std::to_string(rand() % 10);
        }
    } while (numerosCuentasGenerados.find(cuenta) != numerosCuentasGenerados.end());

    numerosCuentasGenerados.insert(cuenta);
    return cuenta;
}

std::string Estudiante::obtenerNombre() const {
    return nombre;
}

int Estudiante::obtenerEdad() const {
    return edad;
}

const std::string& Estudiante::obtenerNumeroCuenta() const {
    return numeroCuenta;
}

const std::vector<std::string>& Estudiante::obtenerMaterias() const {
    return materias;
}

const std::vector<int>& Estudiante::obtenerCalificaciones() const {
    return calificaciones;
}
