#include "Empresa.h"
#include <iostream>

void Empresa::agregarEmpleado(std::unique_ptr<Empleado> empleado) {
    empleados.push_back(std::move(empleado));
}

void Empresa::eliminarEmpleado(int index) {
    if (index >= 0 && index < empleados.size()) {
        empleados.erase(empleados.begin() + index);
    }
}

void Empresa::mostrarEmpleados() const {
    for (const auto& empleado : empleados) {
        std::cout << "Nombre: " << empleado->getNombre()
                  << ", Edad: " << empleado->getEdad()
                  << ", Salario: " << empleado->calcularSalario() << std::endl;
    }
}
