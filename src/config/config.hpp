/*
    Configuraçãoes gerais da aplicação
*/

#pragma once

#include <cstdlib>
#include <PerlinNoise/PerlinNoise.hpp>

// configuração
extern const char* APPLICATION_NAME;

extern const unsigned short FRAME_RATE;

extern const siv::PerlinNoise::seed_type seed; // semente de geração do mundo

// world definitions
extern const char* WORLD_CONFIG_FILE; // arquivo de configuração do mundo

#define MAX_MOBS_SPAWNED 200 // número máximo de mobs que pode existir

// máxima renderização definida em tiles
#define MAX_VERTICAL_RENDERIZATION 120 // renderização máxima vertical (topo-baixo)
#define MAX_HORIZONTAL_RENDERIZATION 160 // renderização máxima horizontal (esquerda-direita)
