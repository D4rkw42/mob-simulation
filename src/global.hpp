/*
    Variáveis e definições globais
*/

#pragma once

#include <memory>
#include <array>

#include "config.hpp"

#include "entity/entity.hpp"
#include "entity/mobs/mobs.hpp"

#include "utils/camera.hpp"
#include "utils/mouse.hpp"

#include "sdl2/graphics/window.hpp"

// declarações gerais
extern std::shared_ptr<Window> window;

// para gestão de eventos
extern Mouse mouse; // definições do mouse

// world variables
extern std::shared_ptr<Camera> camera; // câmera do jogo
extern std::array<std::shared_ptr<Entity>, MAX_MOBS_SPAWNED> mob_list; // lista de mobs
