/*
    Definições gerais para renderização da flora
*/

#pragma once

#include "config/config.hpp"
#include "config/sdl2/graphics/window.hpp"
#include "config/sdl2/graphics/image.hpp"

#include "utils/world/camera.hpp"
#include "utils/world/world-positions.hpp"

#include "world/gen/defs/tile.hpp"
#include "world/gen/defs/plant.hpp"

void generateFlora(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera, WorldPositionsRef worldPosRef, std::array<std::shared_ptr<Plant>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION>& _plants, std::array<std::shared_ptr<Tile>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> tiles);
void renderFlora(RenderData render_data, std::shared_ptr<Camera> camera, std::array<std::shared_ptr<Plant>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> plants);
