/*
    Variáveis e definições globais
*/

#pragma once

#include <memory>
#include <array>
#include <PerlinNoise/PerlinNoise.hpp>
#include <nlohmann/json.hpp>

#include "config/config.hpp"
#include "config/sdl2/graphics/window.hpp"
#include "config/sdl2/graphics/image.hpp"

#include "world/gen/defs/tile.hpp"
#include "world/entity/entity.hpp"
#include "world/entity/mobs/mobs.hpp"

#include "utils/world/camera.hpp"
#include "utils/events/mouse.hpp"

// arquivo de configuração
extern nlohmann::json config;

// declarações para o funcionamento do SDL2
extern ImageCollection imageCollection;

// declarações gerais
extern std::shared_ptr<Window> window;

// definição para perlin noise
extern const siv::PerlinNoise perlin; 

// para gestão de eventos
extern Mouse mouse; // definições do mouse

// world variables
extern std::shared_ptr<Camera> camera; // câmera do jogo

extern std::array<std::shared_ptr<Tile>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> tiles;
extern std::array<std::shared_ptr<Entity>, MAX_MOBS_SPAWNED> mob_list; // lista de mobs
