/*
    Configuraçãoes gerais da aplicação
*/

#include "config.hpp"

#include <cstdlib>

// configuração
const char* APPLICATION_NAME = "Mob Simulation";

const siv::PerlinNoise::seed_type seed = time(0);

// world definitions
const char* WORLD_CONFIG_FILE = "assets/world.json"; // arquivo de configuração do mundo
