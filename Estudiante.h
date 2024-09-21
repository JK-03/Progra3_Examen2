#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include <vector>
#include <set>

class Estudiante {
protected:
    std::string nombre;
    int edad;
    std::string numeroCuenta;
    std::vector<std::string> materias;
    std::vector<int> calificaciones;
    static std::set<std::string> numerosCuentasGenerados;

public:
    Estudiante(const std::string& nombre, int edad);
    virtual ~Estudiante();

    void agregarMateria(const std::string& nombreMateria, int calificacion);
    virtual double promedio() const = 0;

    std::string obtenerNombre() const;
    int obtenerEdad() const;
    const std::string& obtenerNumeroCuenta() const;
    const std::vector<std::string>& obtenerMaterias() const;
    const std::vector<int>& obtenerCalificaciones() const;

private:
    std::string generarNumeroCuenta();
};

#endif // ESTUDIANTE_H
