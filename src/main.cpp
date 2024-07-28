#include <iostream>
#include <cstdlib>
#include <chrono>

#include <SDL2/SDL.h>

#include "global.hpp"
#include "config.hpp"
#include "application.hpp"
#include "event-handler.hpp"

#include "utils/exception.hpp"

#include "sdl2/config.hpp"

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

    while (!SDL_QuitRequested()) {
        SDL_PollEvent(&event);
        handleEvents(event);

        // definição do tempo decorrido

        curr_epoch = epoch_time;
        int elapsedTime = curr_epoch - last_epoch;

        last_epoch = curr_epoch;

        // renderização e atualização
        app::update(elapsedTime);

        frame_rate_count += elapsedTime;

        if (frame_rate_count >= 1000 / FRAME_RATE) {
            frame_rate_count = 0;
            app::render();

            last_fps++;
        }

        // contagem de fps

        fps_count_time += elapsedTime;

        if (fps_count_time >= 1000) {
            std::cout << "FPS: " << last_fps << "\n";
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
