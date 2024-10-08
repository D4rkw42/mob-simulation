/*
    Definições gerais de manipulação de janelas SDL2
*/

#pragma once

#include <memory>
#include <string>
#include <SDL2/SDL.h>

// config

const unsigned short WINDOW_WIDTH = 800;
const unsigned short WINDOW_HEIGHT = 600;

// definição geral de janela
class Window {
    public:
        SDL_Renderer* renderer;
        
        Window(std::string name);
        ~Window();

        void render(void); // renderiza os gráficos
        void clear(void); // limpa a janela

        // dimensões da janela
        void getDimensions(int& width, int& height);

    private:
        SDL_Window* window;
};

// criação dinâmica de janelas
std::shared_ptr<Window> createWindow(std::string name);
