#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include <thread>
#include <atomic>

#include "Proceso.hpp"
#include "CargaDatos.hpp"
#include "AlgoritmoFIFO.hpp"
#include "Metricas.hpp"
#include "Recursos.hpp"
#include "Sincronizacion.hpp"
#include "VisualizacionSincronia.hpp"

// Variables globales compartidas para sincronización
std::atomic<int> cicloGlobal(0);
std::atomic<bool> simulacionActiva(false);

void dibujarGantt(sf::RenderWindow& window, const std::vector<Proceso>& procesos) {
    float x = 50.0f;
    float y = 100.0f;
    float altura = 30.0f;
    float escalaTiempo = 20.0f;

    for (const auto& proceso : procesos) {
        float inicio = proceso.tiempoComienzo * escalaTiempo;
        float duracion = proceso.burstTime * escalaTiempo;

        sf::RectangleShape rect(sf::Vector2f(duracion, altura));
        rect.setPosition(x + inicio, y);
        rect.setFillColor(sf::Color::Green);
        window.draw(rect);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Simulador de Procesos");
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    std::string modoSeleccionado = "FIFO";
    bool botonSimular = false;
    std::vector<Proceso> procesos;
    std::map<std::string, Recurso> recursos;
    std::vector<Accion> acciones;
    std::thread hiloSimulacion;
    float avgWT = 0.0f, avgCT = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
                if (hiloSimulacion.joinable()) hiloSimulacion.join();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Panel de Control");
        ImGui::Text("Selecciona el algoritmo:");
        if (ImGui::RadioButton("FIFO", modoSeleccionado == "FIFO")) modoSeleccionado = "FIFO";
        if (ImGui::RadioButton("Mutex", modoSeleccionado == "mutex")) modoSeleccionado = "mutex";
        if (ImGui::RadioButton("Semáforo", modoSeleccionado == "semaforo")) modoSeleccionado = "semaforo";

        if (ImGui::Button("Simular")) {
            botonSimular = true;
            if (hiloSimulacion.joinable()) hiloSimulacion.join(); // Esperar hilo anterior
            cicloGlobal = 0;
            simulacionActiva = true;

            if (modoSeleccionado == "FIFO") {
                procesos = cargarProcesos("assets/procesos.txt");
                procesos = simularFIFO(procesos);
                avgWT = calcularTiempoEsperaPromedio(procesos);
                avgCT = calcularTiempoFinalizacionPromedio(procesos);
            } else {
                procesos = cargarProcesos("assets/procesos.txt");
                recursos = cargarRecursos("assets/recursos.txt");
                acciones = cargarAcciones("assets/acciones.txt");
                hiloSimulacion = std::thread([&]() {
                    simularSincronizacion(procesos, recursos, acciones, modoSeleccionado);
                });
            }
        }

        ImGui::End();

        window.clear();

        if (botonSimular && modoSeleccionado == "FIFO") {
            dibujarGantt(window, procesos);
            ImGui::Begin("Métricas FIFO");
            ImGui::Text("Tiempo de Espera Promedio: %.2f ciclos", avgWT);
            ImGui::Text("Tiempo de Finalización Promedio: %.2f ciclos", avgCT);
            ImGui::End();
        }

        if (botonSimular && (modoSeleccionado == "mutex" || modoSeleccionado == "semaforo")) {
            mostrarSimulacion(procesos, cicloGlobal.load());
            cicloGlobal++;  // Aumentar el ciclo para visualización
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    if (hiloSimulacion.joinable()) hiloSimulacion.join();
    return 0;
}
