#include "EstudianteLicenciatura.h"

EstudianteLicenciatura::EstudianteLicenciatura(const std::string& nombre, int edad)
    : Estudiante(nombre, edad) {
}

double EstudianteLicenciatura::promedio() const {
    double suma = 0;
    for (int calificacion : calificaciones) {
        suma += calificacion;
    }
    return calificaciones.empty() ? 0 : suma / calificaciones.size();
}
