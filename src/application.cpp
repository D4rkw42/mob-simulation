/*
    Definições da aplicação: inicialização/quiting, rendering e update
*/

#include "application.hpp"

#include "global.hpp"

#include "sdl2/graphics/window.hpp"

// configurações iniciais e quit
void app::ApplicationConfigure(void) {
    window = createWindow(APPLICATION_NAME);
}

void app::ApplicationQuit(void) {

}

// funcionamento geral da aplicação
void app::update(void) {

}

void app::render(void) {

}
