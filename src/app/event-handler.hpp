/*
    Wrapper para manipulação de eventos
*/

#pragma once

#include <SDL2/SDL.h>

// eventos separador por tipo

void eventMouseClick(SDL_Event event);
void eventMouseMove(SDL_Event event);
void eventMouseScrolling(SDL_Event event);

void eventKeyUp(SDL_Event event);
void eventKeyDown(SDL_Event event);

// gerenciar todos os eventos
void handleEvents(SDL_Event event);
