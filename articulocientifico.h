#ifndef ARTICULOCIENTIFICO_H
#define ARTICULOCIENTIFICO_H

#include "Publicacion.h"

class ArticuloCientifico : public Publicacion {
private:
    int indiceImpacto;

public:
    ArticuloCientifico(const std::string& titulo, const std::string& autor, int anioPublicacion, bool disponible, int indiceImpacto);
    int getIndiceImpacto() const;
    std::string getInformacion() const override;
};

#endif // ARTICULOCIENTIFICO_H
