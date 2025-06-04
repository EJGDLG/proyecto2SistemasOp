#include "Recursos.hpp"
#include <fstream>
#include <sstream>

std::vector<Recurso> cargarRecursos(const std::string& archivo) {
    std::vector<Recurso> recursos;
    std::ifstream file(archivo);
    std::string linea;

    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        Recurso r;
        ss >> r.nombre >> r.cantidad;
        recursos.push_back(r);
    }

    return recursos;
}

std::vector<Accion> cargarAcciones(const std::string& archivo) {
    std::vector<Accion> acciones;
    std::ifstream file(archivo);
    std::string linea;

    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        Accion a;
        ss >> a.procesoId >> a.recurso >> a.tipo >> a.inicio >> a.duracion;
        acciones.push_back(a);
    }

    return acciones;
}
