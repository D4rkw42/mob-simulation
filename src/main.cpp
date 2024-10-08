#include <iostream>
#include <cstdlib>
#include <chrono>

#include <SDL2/SDL.h>

#include "global.hpp"

#include "config/config.hpp"
#include "config/sdl2/sdl-config.hpp"

#include "app/application.hpp"
#include "app/event-handler.hpp"

#include "utils/exception.hpp"

using namespace std::chrono;

//

#define SDL_MAIN_HANDLED

// pre-definitions

#define epoch_time duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

// control vars

SDL_Event event;

unsigned long curr_epoch = 0;
unsigned long last_epoch = epoch_time;

int frame_rate_count = 0;

int fps_count_time = 0;
int last_fps = 0;

//

int main(int argc, char* argv[]) {
    // Inicizalização e captura de erros
    try {
        SDL2Configure();
        app::ApplicationConfigure();
    } catch (Exception e) {
        std::cout << e.message();
        return EXIT_FAILURE;
    }

    // configurações da aplicação
    int FRAME_RATE = config["app"]["frame-rate"];

    while (!SDL_QuitRequested()) {
        SDL_PollEvent(&event);
        handleEvents(event);

        // definição do tempo decorrido

        curr_epoch = epoch_time;
        int deltatime = curr_epoch - last_epoch;

        last_epoch = curr_epoch;

        // renderização e atualização
        app::update(deltatime);

        frame_rate_count += deltatime;

        if (frame_rate_count >= 1000 / FRAME_RATE) {
            frame_rate_count = 0;
            app::render();

            last_fps++;
        }

        // contagem de fps

        fps_count_time += deltatime;

        if (fps_count_time >= 1000) {
            fps_count_time = 0;
            last_fps = 0;
        }

        // for convenience
        SDL_Delay(1);
    }

    app::ApplicationQuit();
    SDL2Quit();

    return EXIT_SUCCESS;
}
