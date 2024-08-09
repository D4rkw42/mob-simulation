/*
    Variáveis e definições globais
*/

#include "global.hpp"

// arquivo de configuração
nlohmann::json config;

// declarações para o funcionamento do SDL2
ImageCollection imageCollection;

// definições gerais
std::shared_ptr<Window> window;

// definição para perlin noise
const siv::PerlinNoise perlin = siv::PerlinNoise {seed}; 

// para gestão de eventos
Mouse mouse = {
    0, 0,
    Mouse_Info {false, 0, 0}, // right
    Mouse_Info {false, 0, 0} // left
};

// world variables
std::shared_ptr<Camera> camera;

std::array<std::shared_ptr<Tile>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> tiles;
std::array<std::shared_ptr<Entity>, MAX_MOBS_SPAWNED> mob_list;
