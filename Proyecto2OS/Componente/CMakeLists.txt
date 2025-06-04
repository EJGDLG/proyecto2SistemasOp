cmake_minimum_required(VERSION 3.10)
project(SimuladorPlanificacion)

set(CMAKE_CXX_STANDARD 17)

# Ruta a SFML
set(SFML_DIR "ruta/a/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Incluir ImGui y el binding ImGui-SFML
add_subdirectory(ruta/a/imgui)
add_subdirectory(ruta/a/imgui-sfml)

include_directories(
    include
    ruta/a/imgui
    ruta/a/imgui-sfml
)

add_executable(SimuladorPlanificacion src/main.cpp)

target_link_libraries(SimuladorPlanificacion
    sfml-graphics
    sfml-window
    sfml-system
    imgui
    imgui-sfml
)
