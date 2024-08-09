/*
    Definições da aplicação: inicialização/quiting, rendering e update
*/

#include "application.hpp"

#include "global.hpp"

#include "config/sdl2/graphics/window.hpp"

#include "utils/world/handle-mobs.hpp"
#include "utils/world/camera.hpp"

#include "world/entity/mobs/mobs.hpp"
#include "world/gen/terrain.hpp"

// configurações iniciais e quit
void app::ApplicationConfigure(void) {
    window = createWindow(APPLICATION_NAME);

    // world inicialization
    camera = std::make_shared<Camera>(0, 0);

    // colocando todos os tiles do terreno para nullptr e pré-geração
    tiles.fill(nullptr);
    // generateTerrain(window, camera, tiles);

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
void app::update(int elapsedTime) {
    // atualizando definições de controle
    camera->updateCameraPosition(mouse);

    // static int count = 0;
    // count += elapsedTime;

    // gerando terreno a cada 10 segundos (teste)
    // if (count >= 20000) {
    //    count = 0;
    //    generateTerrain(window, camera, tiles);
    // }

    // atualizando todos os mobs
    for (auto mob : mob_list) {
        if (mob != nullptr) {
            mob->update(elapsedTime);
        }
    }
}

void app::render(void) {
    window->clear();

    // dados básicos para renderização
    RenderData render_data {window, imageCollection};

    // renderizando terreno
    // renderTerrain(window, camera, tiles);

    // renderizando todos os mobs
    for (auto mob : mob_list) {
        if (mob != nullptr) {
            mob->render(render_data, camera);
        }
    }

    window->render();
}
