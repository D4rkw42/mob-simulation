/*
    Definições básicas para renderização de imagem
*/

#include "image.hpp"

#include <SDL2/SDL_image.h>

SDL_Image::SDL_Image(std::shared_ptr<Window> window, std::string file) {
    SDL_Surface* surface = IMG_Load(file.c_str());

    this->texture = SDL_CreateTextureFromSurface(window->renderer, surface);
    SDL_FreeSurface(surface);
}

SDL_Image::~SDL_Image() {
    SDL_DestroyTexture(this->texture);
}

void SDL_Image::render(std::shared_ptr<Window> window, _img_data* data, _img_data* crop_data, bool flipped) {
    SDL_RenderCopyEx(window->renderer, this->texture, crop_data, data, 0, nullptr, flipped? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

// funções auxiliares
void SDL_Image::loadImage(ImageCollection& collection, std::string name, std::shared_ptr<Window> window, std::string file) {
    std::shared_ptr<SDL_Image> m_image = std::make_shared<SDL_Image>(window, file);
    collection[name] = m_image;
}

void SDL_Image::deleteImage(ImageCollection& collection, std::string name) {
    collection.erase(name);
}

void SDL_Image::render(RenderData render_data, std::string name, _img_data* data, _img_data* crop_data, bool flipped) {
    render_data.collection[name]->render(render_data.window, data, crop_data, flipped);
}

bool SDL_Image::exists(ImageCollection& collection, std::string name) {
    // comparação de existência para iterator std::unordered_map<T, Key>::find
    return collection.find(name) != collection.end();
}
