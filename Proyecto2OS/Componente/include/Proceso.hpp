#ifndef PROCESO_HPP
#define PROCESO_HPP

#include <string>

struct Proceso {
    int id;
    int llegada;
    int burstTime;
    int tiempoComienzo;
    int tiempoFinalizacion;
    int tiempoEspera;
};

#endif
