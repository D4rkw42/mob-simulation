/*
    Definição de sprites e animações
*/

#pragma once

#include <vector>
#include <memory>
#include <string>

#include "sdl2/graphics/window.hpp"

// informações básicas para animação
struct AnimationInfo {
    unsigned short width, height;
    unsigned short n_sprites;
    unsigned short duration;
    bool repeat;
};

// classe básica para animações
// sempre chamado no update
class Animation {
    public:
        // carrega dados para uma nova animação
        void set(std::string path, AnimationInfo info);

        void render(std::shared_ptr<Window> window, int x, int y, double scale = 1.f); // renderiza a animação na tela selecionada
        void load(int elapsedTime); // atualiza a animação

        Animation(void);
        ~Animation();

    private:
        AnimationInfo info; // informações de animação
        SDL_Surface* surface;
        unsigned short sprite; // sprite atual
        int count;
};
