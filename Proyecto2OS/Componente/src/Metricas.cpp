#include "Metricas.hpp"

float calcularTiempoEsperaPromedio(const std::vector<Proceso>& procesos) {
    float total = 0;
    for (const auto& p : procesos) {
        total += p.tiempoEspera;
    }
    return procesos.empty() ? 0 : total / procesos.size();
}

float calcularTiempoFinalizacionPromedio(const std::vector<Proceso>& procesos) {
    float total = 0;
    for (const auto& p : procesos) {
        total += p.tiempoFinalizacion;
    }
    return procesos.empty() ? 0 : total / procesos.size();
}
