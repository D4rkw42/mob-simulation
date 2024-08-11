/*
    Configuraçãoes gerais da aplicação
*/

#pragma once

#include <cstdlib>

// configuração
extern const char* APPLICATION_NAME;

// world definitions
extern const char* WORLD_CONFIG_FILE; // arquivo de configuração do mundo

#define MAX_MOBS_SPAWNED 200 // número máximo de mobs que pode existir

// máxima renderização definida em tiles
#define MAX_VERTICAL_RENDERIZATION 120 // renderização máxima vertical (topo-baixo)
#define MAX_HORIZONTAL_RENDERIZATION 180 // renderização máxima horizontal (esquerda-direita)
