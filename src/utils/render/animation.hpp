/*
    Definição de sprites e animações
*/

#pragma once

#include <vector>
#include <memory>
#include <string>

#include "config/sdl2/graphics/window.hpp"
#include "config/sdl2/graphics/image.hpp"
#include "utils/world/camera.hpp"

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
        // general id serve para criar um vínculo único entre estado e o invocador da animação (pode ser indefinido)
        void set(std::string file, AnimationInfo info, std::string general_id = "");

        void render(RenderData render_data, std::shared_ptr<Camera> camera, int x, int y, double scale = 1.f); // renderiza a animação na tela selecionada
        void load(int elapsedTime); // atualiza a animação

        void flip(bool flip); // se a imagem deve ser flippada

        Animation(void);

    private:
        AnimationInfo info; // informações de animação
        std::string file, id;

        bool flipped; // se deve estar rotacionado
        
        int sprite, count; // sprite atual / contagem para sprites
};
