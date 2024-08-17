/*
    Definições básicas para renderização de imagem
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "config/sdl2/graphics/window.hpp"

class SDL_Image;

// estrutura para guarda imagens
typedef std::unordered_map<std::string, std::shared_ptr<SDL_Image>> ImageCollection;

// informações para imagem
typedef SDL_Rect _img_data;

// informações báscias para qualquer desenho (passado para a função)
struct RenderData {
    std::shared_ptr<Window> window;
    ImageCollection& collection;
};

// classe básica para geração de imagens
class SDL_Image {
    public:
        SDL_Image(std::shared_ptr<Window> window, std::string file);
        ~SDL_Image();

        void render(std::shared_ptr<Window> window, _img_data* data, _img_data* crop_data, bool flipped);

        // funções auxiliares
        static void loadImage(ImageCollection& collection, std::string name, std::shared_ptr<Window> window, std::string file);
        static void deleteImage(ImageCollection& collection, std::string name);
        static void render(RenderData render_data, std::string name, _img_data* data, _img_data* crop_data = nullptr, bool flipped = false);

        // verificação se uma imagem existe
        static bool exists(ImageCollection& collection, std::string name);

    private:
        SDL_Texture* texture;
};
