#include "Sincronizacion.hpp"
#include <thread>
#include <mutex>
#include <map>
#include <chrono>
#include <iostream>

std::mutex mtx;

void ejecutarAcciones(std::vector<Proceso>& procesos,
                      std::vector<Recurso>& recursos,
                      const std::vector<Accion>& acciones,
                      const std::string& modo) {
    std::map<std::string, int> disponibilidad;

    for (const auto& r : recursos) {
        disponibilidad[r.nombre] = r.cantidad;
    }

    for (auto& acc : acciones) {
        std::this_thread::sleep_for(std::chrono::milliseconds(acc.inicio * 100));

        if (modo == "mutex") {
            std::lock_guard<std::mutex> lock(mtx);
            if (acc.tipo == "solicitar" && disponibilidad[acc.recurso] > 0) {
                disponibilidad[acc.recurso]--;
                std::cout << "Proceso " << acc.procesoId << " adquirió " << acc.recurso << "\n";
            } else if (acc.tipo == "liberar") {
                disponibilidad[acc.recurso]++;
                std::cout << "Proceso " << acc.procesoId << " liberó " << acc.recurso << "\n";
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(acc.duracion * 100));
    }
}

void simularSincronizacion(std::vector<Proceso>& procesos,
                           std::vector<Recurso>& recursos,
                           const std::vector<Accion>& acciones,
                           const std::string& modo) {
    std::thread t(ejecutarAcciones, std::ref(procesos), std::ref(recursos), acciones, modo);
    t.join();
}
