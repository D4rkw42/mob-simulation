#include <iostream>
#include <cstdlib>

#include <SDL2/SDL.h>

#include "global.hpp"
#include "application.hpp"
#include "event-handler.hpp"

#include "utils/exception.hpp"

#include "sdl2/config.hpp"

#define SDL_MAIN_HANDLED

SDL_Event event;

int main(int argc, char* argv[]) {
    // Inicizalização e captura de erros
    try {
        SDL2Configure();
        app::ApplicationConfigure();
    } catch (Exception e) {
        std::cout << e.message();
        return EXIT_FAILURE;
    }

    while (!SDL_QuitRequested()) {
        SDL_PollEvent(&event);
        handleEvents(event);

        // renderização e atualização
        app::update();
        app::render();
    }

    app::ApplicationQuit();
    SDL2Quit();

    return EXIT_SUCCESS;
}
