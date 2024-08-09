/*
    Definição de sprites e animações
*/

#include "animation.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

Animation::Animation(void) : flipped(false) {};

void Animation::set(std::string file, AnimationInfo info, std::string general_id) {
    this->id = general_id;
    this->info = info;
    this->file = file;

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
            this->sprite = this->info.repeat? 0 : this->info.n_sprites - 1;
        }
    }
}

void Animation::render(RenderData render_data, std::shared_ptr<Camera> camera, int x, int y, double scale) {
    double pos_x, pos_y, _width, _height;

    // calculando posição na tela
    camera->viewport(render_data.window, ObjectInfo {
        static_cast<double>(this->info.width),
        static_cast<double>(this->info.height),
        static_cast<double>(x), static_cast<double>(y)
    }, pos_x, pos_y, _width, _height);

    // posição
    int img_w = _width * scale;
    int img_h = _height * scale;
    int img_x = pos_x - img_w / 2;
    int img_y = pos_y - img_h / 2;

    // recorte
    int img_crop_x = this->info.width * this->sprite;
    int img_crop_y = 0;
    int img_crop_w = this->info.width;
    int img_crop_h = this->info.height;

    _img_data img_data = {img_x, img_y, img_w, img_h};
    _img_data img_crop = {img_crop_x, img_crop_y, img_crop_w, img_crop_h};

    // criando nova imagem caso precise
    if (!SDL_Image::exists(render_data.collection, this->id)) {
        SDL_Image::loadImage(render_data.collection, this->id, render_data.window, this->file);
    }

    SDL_Image::render(render_data, this->id, &img_data, &img_crop, this->flipped);
}

//

void Animation::flip(bool flip) {
    this->flipped = flip;
}
