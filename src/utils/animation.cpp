/*
    Definição de sprites e animações
*/

#include "animation.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

Animation::Animation(void) : surface(nullptr), flipped(false) {};
Animation::~Animation() {
    SDL_FreeSurface(this->surface);
}

void Animation::set(std::string file, AnimationInfo info) {
    if (this->surface != nullptr) {
        SDL_FreeSurface(this->surface);
    }

    this->surface = IMG_Load(file.c_str());
    this->info = info;
    this->sprite = 0;
    this->count = 0;
}

void Animation::load(int elapsedTime) {
    // passando para o próximo sprite
    this->count += elapsedTime;

    if (this->count >= this->info.duration / this->info.n_sprites) {
        this->count = 0;
        this->sprite++;

        // alcaçando o máximo de sprites
        if (this->sprite == this->info.n_sprites) {
            this->sprite = this->info.repeat? 0 : this->info.n_sprites;
        }
    }
}

void Animation::render(std::shared_ptr<Window> window, int x, int y, double scale) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, this->surface);
    SDL_Rect rect_pos, rect_split; // retangulo para posicionamento e para ajuste

    // posição
    rect_pos.w = this->info.width * scale;
    rect_pos.h = this->info.height * scale;
    rect_pos.x = x - rect_pos.w / 2;
    rect_pos.y = y - rect_pos.h / 2;

    // recorte
    rect_split.x = this->info.width * this->sprite;
    rect_split.y = 0;
    rect_split.w = this->info.width;
    rect_split.h = this->info.height;

    SDL_RenderCopyEx(window->renderer, texture, &rect_split, &rect_pos, 0, nullptr, this->flipped? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
}

//

void Animation::flip(bool flip) {
    this->flipped = flip;
}
