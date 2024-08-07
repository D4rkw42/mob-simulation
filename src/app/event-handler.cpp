/*
    Wrapper para manipulação de eventos
*/

#include "event-handler.hpp"

#include "global.hpp"

// eventos separador por tipo

void eventMouseClick(SDL_Event event) {
    // atualizando definições de mouse
    if (event.button.button == SDL_BUTTON_RIGHT) { // atualizando dados para bnt right
        mouse.right.hold = false;

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouse.right.hold = true;
            mouse.right.hold_x = mouse.x;
            mouse.right.hold_y = mouse.y;
        }
    } else { // atualizando dados para bnt left
        mouse.left.hold = false;

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouse.left.hold = true;
            mouse.left.hold_x = mouse.x;
            mouse.left.hold_y = mouse.y;
        }
    }
}

void eventMouseMove(SDL_Event event) {
    // atualizando definições de mouse
    mouse.x = event.motion.x;
    mouse.y = event.motion.y;
}

void eventMouseScrolling(SDL_Event event) {
    // alterando o zoom da câmera
    if (event.wheel.y < 0) {
        camera->zoom_out();
    } else {
        camera->zoom_in();
    }
}

void eventKeyUp(SDL_Event event) {

}

void eventKeyDown(SDL_Event event) {

}

// gerenciar todos os eventos
void handleEvents(SDL_Event event) {
    switch (event.type) {
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
            eventMouseClick(event);
            break;

        case SDL_KEYDOWN:
            eventKeyDown(event);
            break;

        case SDL_KEYUP:
            eventKeyUp(event);
            break;

        case SDL_MOUSEMOTION:
            eventMouseMove(event);
            break;

        case SDL_MOUSEWHEEL:
            eventMouseScrolling(event);
            break;
    }
}
