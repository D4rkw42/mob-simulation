/*
    Definições da aplicação: inicialização/quiting, rendering e update
*/

#include "application.hpp"

#include "global.hpp"

#include "sdl2/graphics/window.hpp"

#include "utils/animation.hpp"
#include <SDL2/SDL.h>

#include <iostream>

Animation animation;

// configurações iniciais e quit
void app::ApplicationConfigure(void) {
    window = createWindow(APPLICATION_NAME);
    AnimationInfo info = {64, 32, 5, 600, true};
    animation.set("assets/sprites/entity/wolf/walking.png", info);
}

void app::ApplicationQuit(void) {

}

// funcionamento geral da aplicação
void app::update(int elapsedTime) {
    animation.load(elapsedTime);
}

void app::render(void) {
    SDL_RenderClear(window->renderer);
    animation.render(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 4);
    SDL_RenderPresent(window->renderer);
}
