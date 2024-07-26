/*
    Wrapper para manipulação de eventos
*/

#include "event-handler.hpp"

// eventos separador por tipo

void eventMouseClick(SDL_Event event) {

}

void eventMouseMove(SDL_Event event) {

}

void eventMouseScrolling(SDL_Event event) {

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
