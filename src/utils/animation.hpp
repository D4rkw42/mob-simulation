/*
    Definição de sprites e animações
*/

#pragma once

#include <vector>
#include <memory>
#include <string>

#include "sdl2/graphics/window.hpp"
#include "utils/camera.hpp"

// informações básicas para animação
struct AnimationInfo {
    int width, height;
    int n_sprites;
    int duration;
    bool repeat;
};

// classe básica para animações
// sempre chamado no update
class Animation {
    public:
        // carrega dados para uma nova animação
        void set(std::string file, AnimationInfo info);

        void render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera, int x, int y, double scale = 1.f); // renderiza a animação na tela selecionada
        void load(int elapsedTime); // atualiza a animação

        void flip(bool flip); // se a imagem deve ser flippada

        Animation(void);
        ~Animation();

    private:
        AnimationInfo info; // informações de animação
        SDL_Surface* surface;
        int sprite; // sprite atual
        bool flipped; // se deve estar rotacionado
        int count;
};
