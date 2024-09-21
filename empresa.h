#ifndef EMPRESA_H
#define EMPRESA_H

#include <vector>
#include <memory>
#include "Empleado.h"

class Empresa {
private:
    std::vector<std::unique_ptr<Empleado>> empleados;

public:
    void agregarEmpleado(std::unique_ptr<Empleado> empleado);
    void eliminarEmpleado(int index);
    void mostrarEmpleados() const;
};

#endif // EMPRESA_H
