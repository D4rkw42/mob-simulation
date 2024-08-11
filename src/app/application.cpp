/*
    Definições da aplicação: inicialização/quiting, rendering e update
*/

#include "application.hpp"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <FastNoise/FastNoiseLite.h>

#include "global.hpp"

#include "config/sdl2/graphics/window.hpp"

#include "utils/world/handle-mobs.hpp"
#include "utils/world/camera.hpp"

#include "world/entity/mobs/mobs.hpp"
#include "world/gen/terrain.hpp"

using json = nlohmann::json;

// configurações iniciais e quit
void app::ApplicationConfigure(void) {
    // abrindo configurações da aplicação
    std::ifstream config_file("assets/config.json");
    config = json::parse(config_file);

    // demais configurações
    perlin_noise = FastNoiseLite(1000);
    voronoi_noise = FastNoiseLite(1000);

    perlin_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    voronoi_noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);

    // inciando janela
    window = createWindow(APPLICATION_NAME);

    // world inicialization
    camera = std::make_shared<Camera>(0, 0);

    // pré-geração de mundo
    generateTerrain(window, camera, tiles); // terreno

    // colocando todos os objetos de mob_list para nullptr
    mob_list.fill(nullptr);

    spawnNewMob<Wolf>(mob_list, 0, 0);
}

void app::ApplicationQuit(void) {
    // deleting sdl config vars
    imageCollection.clear();

    // deleting world vars
    tiles.fill(nullptr);
    mob_list.fill(nullptr);
}

// funcionamento geral da aplicação
void app::update(int deltatime) {
    // atualizando definições de controle
    camera->updateCameraPosition(mouse);

    // geração de terreno
    static int gen_count = 0;
    gen_count += deltatime;

    // gera novo terreno a cada 0,3 s
    if (gen_count > 300) {
        generateTerrain(window, camera, tiles);
        gen_count = 0;
    }

    // atualizando todos os mobs
    for (auto mob : mob_list) {
        if (mob == nullptr) {
            break;
        }
        mob->update(deltatime);
    }
}

void app::render(void) {
    window->clear();

    // dados básicos para renderização
    RenderData render_data {window, imageCollection};

    // renderizando terreno
    renderTerrain(render_data, camera, tiles);

    // renderizando todos os mobs
    for (auto mob : mob_list) {
        if (mob == nullptr) {
            break;
        }
        mob->render(render_data, camera);
    }

    window->render();
}
