/*
    Definições básicas de câmera
*/

#pragma once

#include <memory>

#include "config/sdl2/graphics/window.hpp"
#include "utils/events/mouse.hpp"

// definições
extern double MAX_ZOOM; // zoom máximo permitido
extern double MIN_ZOOM; // zoom mínimo permitido
extern double ZOOM_INITIAL; // zoom inicial

extern double ZOOM_MOD; // alteração do zoom

// dados que serão passados como referência dos cálculos
struct ObjectInfo {
    double width, height, x, y;
};

// classe básica
class Camera {
    public:
        double x, y;
        Camera(int x, int y);

        // cálculo de coordenadas
        void viewport(std::shared_ptr<Window> window, ObjectInfo info, double& x, double& y, double& width, double& height);

        // controle de posição
        void zoom_in(void); // aumenta o zoom
        void zoom_out(void); // dimunui o zoom

        void updateCameraPosition(Mouse mouse); // move a câmera de lugar

        // funções auxiliares

        // obtém o quanto do mundo a câmera está capturando (com acréscimo de 10%)
        void getRenderDistance(std::shared_ptr<Window> window, double& dist_horiz, double& dist_vert);

    private:
        double zoom;
};
