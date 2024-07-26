/*
    Configurações iniciais do SDL2 Library
*/

#include "config.hpp"

#include <SDL2/SDL.h>

#include "utils/exception.hpp"

void SDL2Configure(void) {
    bool SDLInitSucess = SDL_Init(SDL_INIT_VIDEO);

    if (SDLInitSucess) {
        throw Exception("Cannot initialize SDL2.", SDL_GetError());
    }
}

void SDL2Quit(void) {
    SDL_Quit();
}
