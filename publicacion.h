#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <string>

class Publicacion {
protected:
    std::string titulo;
    std::string autor;
    int anioPublicacion;
    bool disponible;

public:
    Publicacion(const std::string& titulo, const std::string& autor, int anioPublicacion, bool disponible);
    virtual ~Publicacion();

    std::string getTitulo() const;
    std::string getAutor() const;
    int getAnioPublicacion() const;
    bool isDisponible() const;

    void setDisponible(bool disponible);
    virtual std::string getInformacion() const = 0;
};

#endif // PUBLICACION_H
