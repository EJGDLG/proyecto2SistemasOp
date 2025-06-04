#include "CargaDatos.hpp"
#include <fstream>
#include <sstream>

std::vector<Proceso> cargarProcesos(const std::string& archivo) {
    std::vector<Proceso> procesos;
    std::ifstream file(archivo);
    std::string linea;

    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        Proceso p;
        ss >> p.id >> p.llegada >> p.burstTime;
        procesos.push_back(p);
    }

    return procesos;
}

