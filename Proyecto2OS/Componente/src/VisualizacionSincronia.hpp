#include "VisualizacionSincronia.hpp"
#include <imgui.h>

void mostrarSimulacion(const std::vector<Proceso>& procesos, int ciclo) {
    ImGui::Begin("Visualización de Sincronización");

    ImGui::Text("Ciclo actual: %d", ciclo);
    ImGui::Separator();

    for (const auto& p : procesos) {
        std::string etiqueta = "Proceso " + std::to_string(p.id);
        float progreso = 0.0f;

        if (ciclo >= p.tiempoComienzo && ciclo < p.tiempoFinalizacion) {
            progreso = (float)(ciclo - p.tiempoComienzo) / (p.tiempoFinalizacion - p.tiempoComienzo);
        } else if (ciclo >= p.tiempoFinalizacion) {
            progreso = 1.0f;
        }

        ImGui::ProgressBar(progreso, ImVec2(0.8f * ImGui::GetWindowWidth(), 0), etiqueta.c_str());
    }

    ImGui::End();
}
