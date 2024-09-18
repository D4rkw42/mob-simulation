/*
    Definições do algoritmo wavefront
*/

#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "world/world.hpp"

#include "utils/math/math-basics.hpp"
#include "utils/math/collision.hpp"

/*
 * estrutura básica de dados para calcular o wavefront
 *
 * dist = 0 -> node válido
 * dist = -1 -> node inválido
 * dist > 0 -> node já calculado
 * 
 */
struct Node {
    WorldCoord coord;
    int x, y; // apenas em relação a grid
    int dist;
};

// configuração

// tiles inválidos
extern std::vector<std::string> invalidTiles;

// criação dinâmica de nodes
Node createNode(int x, int y, int dist = 0);

// criar uma grid de nodes para o wavefront
std::vector<std::vector<Node>> createWaveFrontGrid(World world, WorldCoord origin, WorldCoord destiny, Hitbox hitbox);
std::vector<WorldCoord> wavefront(World world, WorldCoord origin, WorldCoord destiny, Hitbox hitbox);
