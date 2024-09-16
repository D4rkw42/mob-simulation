/*
    Variáveis e definições globais
*/

#pragma once

#include <memory>
#include <array>
#include <FastNoise/FastNoiseLite.h>
#include <nlohmann/json.hpp>

#include "config/config.hpp"
#include "config/sdl2/graphics/window.hpp"
#include "config/sdl2/graphics/image.hpp"

#include "world/world.hpp"

#include "utils/world/camera.hpp"
#include "utils/events/mouse.hpp"

// arquivo de configuração
extern nlohmann::json config;

// declarações para o funcionamento do SDL2
extern ImageCollection imageCollection;

// declarações gerais
extern std::shared_ptr<Window> window;

// definição para noises
extern FastNoiseLite perlin_noise;
extern FastNoiseLite voronoi_noise;

// para gestão de eventos
extern Mouse mouse; // definições do mouse

// world variables
extern std::shared_ptr<Camera> camera; // câmera do jogo

extern World world; // representação do mundo
