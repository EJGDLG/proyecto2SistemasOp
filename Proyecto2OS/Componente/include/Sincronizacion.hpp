#ifndef SINCRONIZACION_HPP
#define SINCRONIZACION_HPP

#include <vector>
#include <string>
#include "Proceso.hpp"
#include "Recursos.hpp"

void simularSincronizacion(std::vector<Proceso>& procesos,
                           std::vector<Recurso>& recursos,
                           const std::vector<Accion>& acciones,
                           const std::string& modo);

#endif
