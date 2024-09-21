#ifndef ESTUDIANTELICENCIATURA_H
#define ESTUDIANTELICENCIATURA_H

#include "Estudiante.h"

class EstudianteLicenciatura : public Estudiante {
public:
    EstudianteLicenciatura(const std::string& nombre, int edad);
    double promedio() const override;
};

#endif // ESTUDIANTELICENCIATURA_H
