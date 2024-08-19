/*
    Definição de tile
*/

#pragma once

#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "config/sdl2/graphics/window.hpp"
#include "config/sdl2/graphics/image.hpp"

#include "utils/math/math.hpp"
#include "utils/world/camera.hpp"

// definições
extern const char* TILE_IMG_PATH; // caminho para as imagens de cada tile

class Tile {
    public:
        std::string file;
        std::string name, biome;
        int variation;

        int x, y, width;
        Hitbox hitbox;

        Tile(std::string name, std::string biome, int variation, int x, int y, int width);

        void render(RenderData render_data, std::shared_ptr<Camera> camera);
};
