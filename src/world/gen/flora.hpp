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

void generateFlora(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera, WorldPositionsRef worldPosRef, PlantList& _plants, TileList tiles);
void renderFlora(RenderData render_data, std::shared_ptr<Camera> camera, PlantList plants);
