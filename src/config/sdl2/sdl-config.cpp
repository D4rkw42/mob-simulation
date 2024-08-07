/*
    Configurações iniciais do SDL2 Library
*/

#include "sdl-config.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "utils/exception.hpp"

void SDL2Configure(void) {
    bool SDLInitSuccess = SDL_Init(SDL_INIT_VIDEO);
    bool SDLImageInitSuccess = IMG_Init(IMG_INIT_PNG);

    if (SDLInitSuccess || !SDLImageInitSuccess) {
        throw Exception("Cannot initialize SDL2.", SDL_GetError());
    }
}

void SDL2Quit(void) {
    IMG_Quit();
    SDL_Quit();
}
