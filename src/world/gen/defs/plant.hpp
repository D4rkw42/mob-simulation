/*
    Definições gerais para planta
*/

#pragma once

#include <memory>
#include <string>
#include <array>

#include "config/sdl2/graphics/image.hpp"
#include "config/sdl2/graphics/window.hpp"

#include "utils/world/camera.hpp"
#include "utils/math/math.hpp"

class Plant {
    public:
        std::string type;

        int x, y, width, height; // posição e tamanho
        Hitbox hitbox;

        double scale; // escala de desenho

        // informações importantes
        int offset_x, offset_y; // desvio para desenho

        Plant(std::string type, int x, int y);

        void render(RenderData render_data, std::shared_ptr<Camera> camera);
};
