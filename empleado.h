#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <string>

class Empleado {
protected:
    std::string nombre;
    int edad;
    float salario;

public:
    Empleado(const std::string& nombre, int edad, float salario);
    virtual ~Empleado();
    virtual float calcularSalario() const = 0;

    std::string getNombre() const;
    int getEdad() const;
    float getSalario() const;
};

#endif // EMPLEADO_H
