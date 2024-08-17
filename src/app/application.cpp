/*
    Definições da aplicação: inicialização/quiting, rendering e update
*/

#include "application.hpp"

#include <ctime>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <FastNoise/FastNoiseLite.h>

#include "global.hpp"

#include "config/sdl2/graphics/window.hpp"

#include "utils/world/handle-mobs.hpp" // retirar dps
#include "utils/world/handle-plants.hpp" // retirar dps
#include "utils/world/camera.hpp"
#include "utils/world/world-positions.hpp"

#include "world/entity/mobs/mobs.hpp"
#include "world/gen/terrain.hpp"
#include "world/gen/flora.hpp"

using json = nlohmann::json;

// configurações iniciais e quit
void app::ApplicationConfigure(void) {
    // abrindo configurações da aplicação
    std::ifstream config_file("assets/config.json");
    config = json::parse(config_file);

    // demais configurações
    perlin_noise = FastNoiseLite(2000);
    voronoi_noise = FastNoiseLite(2000);

    perlin_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    voronoi_noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);

    // inciando janela
    window = createWindow(APPLICATION_NAME);

    // world inicialization
    camera = std::make_shared<Camera>(0, 0);

    // setando valores do mundo previamente
    tiles.fill(nullptr);
    plants.fill(nullptr);

    // pré-geração de mundo
    auto worldPositionsRef = calculateWorldPosition(window, camera);

    generateTerrain(window, camera, worldPositionsRef, tiles); // terreno
    generateFlora(window, camera, worldPositionsRef, plants, tiles);

    delete[] worldPositionsRef.worldPositions;

    // colocando todos os objetos de mob_list para nullptr
    mob_list.fill(nullptr);
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

    // obtendo dados dinâmicos
    double dist_horiz, dist_vert; // distância de renderização
    camera->getRenderDistance(window, dist_horiz, dist_vert);

    // geração de terreno
    static int gen_count = 0;
    gen_count += deltatime;

    // gera o mundo a cada 0,3 s
    if (gen_count > 300) {

        auto worldPositionsRef = calculateWorldPosition(window, camera);

        generateTerrain(window, camera, worldPositionsRef, tiles); // terreno
        generateFlora(window, camera, worldPositionsRef, plants, tiles); // flora

        delete[] worldPositionsRef.worldPositions;

        gen_count = 0;
    }

    // atualizando todos os mobs
    for (int i = 0; i < mob_list.size(); ++i) {
        if (mob_list[i] == nullptr) {
            break;
        }

        // eliminando mobs que estão fora do alcance de renderização
        if (mob_list[i]->x > camera->x + dist_horiz / 2 || mob_list[i]->x < camera->x - dist_horiz / 2) {
            mob_list[i] = nullptr;
            continue;
        }

        if (mob_list[i]->y > camera->y + dist_vert / 2 || mob_list[i]->y < camera->y - dist_vert / 2) {
            mob_list[i] = nullptr;
            continue;
        }

        mob_list[i]->update(deltatime);
    }
}

void app::render(void) {
    window->clear();

    // dados básicos para renderização
    RenderData render_data {window, imageCollection};

    // renderizando terreno
    renderTerrain(render_data, camera, tiles);
    renderFlora(render_data, camera, plants);

    // renderizando todos os mobs
    for (auto mob : mob_list) {
        if (mob == nullptr) {
            break;
        }
        mob->render(render_data, camera);
    }

    window->render();
}
