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
    TileList tiles;
    PlantList plants;
    MobList mob_list; // lista de mobs
};
