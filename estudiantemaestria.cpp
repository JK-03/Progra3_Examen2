#include "EstudianteMaestria.h"
#include <algorithm>

EstudianteMaestria::EstudianteMaestria(const std::string& nombre, int edad)
    : Estudiante(nombre, edad) {
}

double EstudianteMaestria::promedio() const {
    if (calificaciones.empty()) return 0;

    int calificacionMinima = *std::min_element(calificaciones.begin(), calificaciones.end());
    double suma = 0;
    int contador = 0;

    for (int calificacion : calificaciones) {
        if (calificacion != calificacionMinima || contador > 0) {
            suma += calificacion;
            contador++;
        }
    }
    return suma / (calificaciones.size() - 1);
}
