#include "AlgoritmoFIFO.hpp"
#include <algorithm>

std::vector<Proceso> simularFIFO(std::vector<Proceso> procesos) {
    std::sort(procesos.begin(), procesos.end(), [](const Proceso& a, const Proceso& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int tiempoActual = 0;
    for (auto& proceso : procesos) {
        if (tiempoActual < proceso.arrivalTime) {
            tiempoActual = proceso.arrivalTime;
        }
        proceso.tiempoComienzo = tiempoActual;
        proceso.tiempoFinalizacion = tiempoActual + proceso.burstTime;
        proceso.turnaroundTime = proceso.tiempoFinalizacion - proceso.arrivalTime;
        proceso.tiempoEspera = proceso.turnaroundTime - proceso.burstTime;
        tiempoActual = proceso.tiempoFinalizacion;
    }

    return procesos;
}
