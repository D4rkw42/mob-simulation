/*
    Definições para manipulação de plantas
*/

#pragma once

#include <memory>

#include "config/config.hpp"

#include "world/gen/defs/plant.hpp"

// cria uma planta no mapa
void createNewPlant(std::array<std::shared_ptr<Plant>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION>& plants, std::string type, int x, int y);
