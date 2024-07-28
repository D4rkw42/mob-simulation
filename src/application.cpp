/*
    Definições da aplicação: inicialização/quiting, rendering e update
*/

#include "application.hpp"

#include "global.hpp"

#include "sdl2/graphics/window.hpp"

#include "entity/mobs/mobs.hpp"
#include "utils/handle-mobs.hpp"

// configurações iniciais e quit
void app::ApplicationConfigure(void) {
    window = createWindow(APPLICATION_NAME);

    // world inicialization

    // colocando todos os objetos de mob_list para nullptr
    mob_list.fill(nullptr);

    spawnNewMob<Wolf>(mob_list, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void app::ApplicationQuit(void) {
    
}

// funcionamento geral da aplicação
void app::update(int elapsedTime) {
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
            mob->render(window);
        }
    }

    window->render();
}
