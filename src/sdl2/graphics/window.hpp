/*
    Definições gerais de manipulação de janelas SDL2
*/

#pragma once

#include <memory>
#include <string>
#include <SDL2/SDL.h>

// config

const unsigned int WINDOW_WIDTH = 600;
const unsigned int WINDOW_HEIGHT = 400;

// definição geral de janela
class Window {
    public:
        Window(std::string name);
        ~Window();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};

// criação dinâmica de janelas
std::shared_ptr<Window> createWindow(std::string name);
