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

// definição para noises
FastNoiseLite perlin_noise;
FastNoiseLite voronoi_noise;

// para gestão de eventos
Mouse mouse = {
    0, 0,
    Mouse_Info {false, 0, 0}, // right
    Mouse_Info {false, 0, 0} // left
};

// world variables
std::shared_ptr<Camera> camera;

World world; // representação do mundo
