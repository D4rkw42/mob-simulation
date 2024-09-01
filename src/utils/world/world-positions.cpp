/*
    Calcula as posições para geração de mundo
*/

#include "world-positions.hpp"

#include "config/config.hpp"

//
const int TILE_SIZE = 30;
const int MAX_WORLD_POSITIONS = MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION;

WorldPositionsRef calculateWorldPosition(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera) {
    WorldPositionsRef worldPositionsRef;
    worldPositionsRef.worldPositions = new WorldCoord[MAX_WORLD_POSITIONS];

    double dist_horiz, dist_vert;
    camera->getRenderDistance(window, dist_horiz, dist_vert);

    int n_horiz_tiles = dist_horiz / TILE_SIZE;
    int n_vert_tiles = dist_vert / TILE_SIZE;

    if (n_horiz_tiles % 2 != 0) {
        n_horiz_tiles--;
    }

    if (n_vert_tiles % 2 != 0) {
        n_vert_tiles--;
    }

    if (n_horiz_tiles > MAX_HORIZONTAL_RENDERIZATION) {
        n_horiz_tiles = MAX_HORIZONTAL_RENDERIZATION;
    }

    if (n_vert_tiles > MAX_VERTICAL_RENDERIZATION) {
        n_vert_tiles = MAX_VERTICAL_RENDERIZATION;
    }

    // posição de referência para a geração
    int center_x = static_cast<int>(camera->x) - static_cast<int>(camera->x) % TILE_SIZE;
    int center_y = static_cast<int>(camera->y) - static_cast<int>(camera->y) % TILE_SIZE;

    // posições iniciais e finais de geração
    int start_x = center_x - TILE_SIZE * n_horiz_tiles / 2;
    int start_y = center_y - TILE_SIZE * n_vert_tiles / 2;

    int final_x = center_x + TILE_SIZE * n_horiz_tiles / 2;
    int final_y = center_y + TILE_SIZE * n_vert_tiles / 2;

    // id para alocação na memória
    int id = 0;

    // obtendo cada posição
    for (int x = start_x; x < final_x; x += TILE_SIZE) {
        for (int y = start_y; y < final_y; y += TILE_SIZE) {
            worldPositionsRef.worldPositions[id++] = WorldCoord {x, y}; // guardando as posições numa lista
        }
    }

    worldPositionsRef.maxIDGenerated = id;

    return worldPositionsRef;
}
