/*
    Definições da aplicação: inicialização/quiting, rendering e update
*/

#include "application.hpp"

#include "global.hpp"

#include "sdl2/graphics/window.hpp"

#include "entity/mobs/mobs.hpp"
#include "utils/handle-mobs.hpp"
#include "utils/camera.hpp"

// configurações iniciais e quit
void app::ApplicationConfigure(void) {
    window = createWindow(APPLICATION_NAME);

    // world inicialization
    camera = std::make_shared<Camera>(0, 0);

    // colocando todos os objetos de mob_list para nullptr
    mob_list.fill(nullptr);

    spawnNewMob<Wolf>(mob_list, 0, 0);
}

void app::ApplicationQuit(void) {
    
}

// funcionamento geral da aplicação
void app::update(int elapsedTime) {
    // atualizando definições de controle
    camera->updateCameraPosition(mouse);

    // atualizando todos os mobs
    for (auto mob : mob_list) {
        if (mob != nullptr) {
            mob->update(elapsedTime);
        }
    }
}

void app::render(void) {
    window->clear();

    // rendering field

    // renderizando todos os mobs
    for (auto mob : mob_list) {
        if (mob != nullptr) {
            mob->render(window, camera);
        }
    }

    window->render();
}
