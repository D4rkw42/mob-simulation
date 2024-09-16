/*
    Definições gerais para planta
*/

#pragma once

#include <memory>
#include <string>
#include <array>

#include "config/config.hpp"
#include "config/sdl2/graphics/image.hpp"
#include "config/sdl2/graphics/window.hpp"

#include "utils/world/camera.hpp"
#include "utils/math/collision.hpp"

// pré-definição
class Plant;

typedef std::array<std::shared_ptr<Plant>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> PlantList;

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
