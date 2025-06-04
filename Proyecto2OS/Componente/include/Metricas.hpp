#ifndef METRICAS_HPP
#define METRICAS_HPP

#include <vector>
#include "Proceso.hpp"

float calcularTiempoEsperaPromedio(const std::vector<Proceso>& procesos);
float calcularTiempoFinalizacionPromedio(const std::vector<Proceso>& procesos);

#endif
