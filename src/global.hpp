/*
    Variáveis e definições globais
*/

#pragma once

#include <memory>
#include <array>

#include "config.hpp"

#include "entity/entity.hpp"
#include "entity/mobs/mobs.hpp"

#include "sdl2/graphics/window.hpp"

// declarações gerais
extern std::shared_ptr<Window> window;

// world variables
extern std::array<std::shared_ptr<Entity>, MAX_MOBS_SPAWNED> mob_list;
