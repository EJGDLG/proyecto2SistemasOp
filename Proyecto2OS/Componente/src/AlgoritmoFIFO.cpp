#include "AlgoritmoFIFO.hpp"
#include <algorithm>

std::vector<Proceso> simularFIFO(std::vector<Proceso> procesos) {
    std::sort(procesos.begin(), procesos.end(), [](const Proceso& a, const Proceso& b) {
        return a.llegada < b.llegada;
    });

    int tiempoActual = 0;

    for (auto& p : procesos) {
        if (tiempoActual < p.llegada) {
            tiempoActual = p.llegada;
        }
        p.tiempoComienzo = tiempoActual;
        p.tiempoFinalizacion = tiempoActual + p.burstTime;
        p.tiempoEspera = p.tiempoComienzo - p.llegada;
        tiempoActual = p.tiempoFinalizacion;
    }

    return procesos;
}
