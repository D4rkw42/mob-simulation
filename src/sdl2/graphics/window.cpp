/*
    Definições gerais de manipulação de janelas SDL2
*/

#include "window.hpp"

#include "utils/exception.hpp"

// definição geral de janela
Window::Window(std::string name) {
    SDL_Window* _window = SDL_CreateWindow(
                                    name.c_str(),
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGHT,
                                    SDL_WINDOW_RESIZABLE
                                );

    // window não criada
    if (_window == nullptr) {
        throw Exception("Window cannot be initialize", SDL_GetError());
    }

    // atribuição
    this->window = _window;
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    // configuração da janela
    SDL_SetWindowMinimumSize(this->window, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Window::render(void) {
    SDL_RenderPresent(this->renderer);
}

void Window::clear(void) {
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->renderer);
}

//

std::shared_ptr<Window> createWindow(std::string name) {
    return std::make_shared<Window>(name);
}
