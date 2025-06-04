#ifndef RECURSOS_HPP
#define RECURSOS_HPP

#include <string>
#include <vector>

struct Recurso {
    std::string nombre;
    int cantidad;
};

struct Accion {
    int procesoId;
    std::string recurso;
    std::string tipo;  // "solicitar" o "liberar"
    int inicio;
    int duracion;
};

std::vector<Recurso> cargarRecursos(const std::string& archivo);
std::vector<Accion> cargarAcciones(const std::string& archivo);

#endif
