/*
    Calcula as posições para geração de mundo
*/

#pragma once

#include "config/sdl2/graphics/window.hpp"
#include "utils/world/camera.hpp"

#include "utils/math/math-basics.hpp"

//
extern const int TILE_SIZE; // tamanho real de cada tile no mundo
extern const int MAX_WORLD_POSITIONS; // quantidade máxima de entidades geradas no terreno do mundo

struct WorldPositionsRef {
    WorldCoord* worldPositions;
    int maxIDGenerated;
};

// calcula todas as posições do mundo para geração

WorldPositionsRef calculateWorldPosition(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera);
