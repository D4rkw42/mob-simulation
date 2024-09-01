/*
    Definição de estrutura de dados do munto
*/

#pragma once

#include <memory>
#include <array>

#include "config/config.hpp"

#include "world/gen/defs/tile.hpp"
#include "world/gen/defs/plant.hpp"
#include "world/entity/entity.hpp"

// definição de posição
struct WorldCoord {
    int x, y;
};

// agrupando os principais conjuntos de dados do mundo
struct World {
    std::array<std::shared_ptr<Tile>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> tiles;
    std::array<std::shared_ptr<Plant>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> plants;
    std::array<std::shared_ptr<Entity>, MAX_MOBS_SPAWNED> mob_list; // lista de mobs
};
