#ifndef REVISTA_H
#define REVISTA_H

#include "Publicacion.h"

class Revista : public Publicacion {
private:
    int numeroEdicion;

public:
    Revista(const std::string& titulo, const std::string& autor, int anioPublicacion, bool disponible, int numeroEdicion);
    int getNumeroEdicion() const;
    std::string getInformacion() const override;
};

#endif // REVISTA_H
