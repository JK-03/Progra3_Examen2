#ifndef LIBRO_H
#define LIBRO_H

#include "Publicacion.h"

class Libro : public Publicacion {
private:
    int numeroPaginas;

public:
    Libro(const std::string& titulo, const std::string& autor, int anioPublicacion, bool disponible, int numeroPaginas);

    int getNumeroPaginas() const;

    std::string getInformacion() const override;
};

#endif // LIBRO_H
