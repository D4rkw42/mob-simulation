/*
    Definições para geração/renderização de terreno
*/

#pragma once

#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "config/config.hpp"
#include "global.hpp"

#include "config/sdl2/graphics/window.hpp"
#include "config/sdl2/graphics/image.hpp"
#include "utils/world/camera.hpp"

#include "world/gen/defs/tile.hpp"

extern const unsigned int TILE_SIZE; // tamanho real de cada tile no mundo

void generateTerrain(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera, std::array<std::shared_ptr<Tile>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION>& _tiles);
void renderTerrain(RenderData render_data, std::shared_ptr<Camera> camera, std::array<std::shared_ptr<Tile>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> tiles);
