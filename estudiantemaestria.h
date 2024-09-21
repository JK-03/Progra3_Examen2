#ifndef ESTUDIANTEMAESTRIA_H
#define ESTUDIANTEMAESTRIA_H

#include "Estudiante.h"

class EstudianteMaestria : public Estudiante {
public:
    EstudianteMaestria(const std::string& nombre, int edad);
    double promedio() const override;
};

#endif // ESTUDIANTEMAESTRIA_H
