/*
    Definição de tile
*/

#pragma once

#include <memory>
#include <string>
#include <array>

#include <SDL2/SDL.h>

#include "config/config.hpp"
#include "config/sdl2/graphics/window.hpp"
#include "config/sdl2/graphics/image.hpp"

#include "utils/world/camera.hpp"
#include "utils/math/collision.hpp"

// pré-definição
class Tile;

// definições
extern const char* TILE_IMG_PATH; // caminho para as imagens de cada tile

typedef std::array<std::shared_ptr<Tile>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> TileList;

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

std::shared_ptr<Tile> findTile(TileList tiles, int x, int y);
