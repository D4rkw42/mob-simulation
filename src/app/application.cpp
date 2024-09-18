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

#include "utils/world/camera.hpp"
#include "utils/world/world-positions.hpp"

#include "world/entity/mobs/mobs.hpp"
#include "world/gen/terrain.hpp"
#include "world/gen/flora.hpp"

// apenas para desenvolvimento -- remover depois
#include "utils/world/handle-mobs.hpp"

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
    world.tiles.fill(nullptr);
    world.plants.fill(nullptr);

    // pré-geração de mundo
    auto worldPositionsRef = calculateWorldPosition(window, camera);

    generateTerrain(window, camera, worldPositionsRef, world.tiles); // terreno
    generateFlora(window, camera, worldPositionsRef, world.plants, world.tiles);

    delete[] worldPositionsRef.worldPositions;

    // colocando todos os objetos de world.mob_list para nullptr
    world.mob_list.fill(nullptr);

    // apenas para desenvolvimento -- remover depois

    spawnNewMob<Wolf>(world.mob_list, 0, 0);
}

void app::ApplicationQuit(void) {
    // deleting sdl config vars
    imageCollection.clear();

    // deleting world vars
    world.tiles.fill(nullptr);
    world.mob_list.fill(nullptr);
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

        generateTerrain(window, camera, worldPositionsRef, world.tiles); // terreno
        generateFlora(window, camera, worldPositionsRef, world.plants, world.tiles); // flora

        delete[] worldPositionsRef.worldPositions;

        gen_count = 0;
    }

    // atualizando todos os mobs
    for (int i = 0; i < world.mob_list.size(); ++i) {
        if (world.mob_list[i] == nullptr) {
            break;
        }

        // eliminando mobs que estão fora do alcance de renderização
        if (world.mob_list[i]->x > camera->x + dist_horiz / 2 || world.mob_list[i]->x < camera->x - dist_horiz / 2) {
            world.mob_list[i] = nullptr;
            continue;
        }

        if (world.mob_list[i]->y > camera->y + dist_vert / 2 || world.mob_list[i]->y < camera->y - dist_vert / 2) {
            world.mob_list[i] = nullptr;
            continue;
        }

        world.mob_list[i]->update(deltatime);
    }
}

void app::render(void) {
    window->clear();

    // dados básicos para renderização
    RenderData render_data {window, imageCollection};

    // renderizando terreno
    renderTerrain(render_data, camera, world.tiles);
    renderFlora(render_data, camera, world.plants);

    // renderizando todos os mobs
    for (auto mob : world.mob_list) {
        if (mob == nullptr) {
            break;
        }

        mob->render(render_data, camera);
    }

    window->render();
}
