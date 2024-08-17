/*
    Definição de tile
*/

#include "tile.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

// definições
const char* TILE_IMG_PATH = "assets/images/world/terrain/";

Tile::Tile(std::string name, std::string biome, int variation, int x, int y, int width) : name(name + std::to_string(variation)), biome(biome), variation(variation), x(x), y(y), width(width) {
    this->file = std::string(TILE_IMG_PATH) + name + "/" + this->name + ".jpg";
}

void Tile::render(RenderData render_data, std::shared_ptr<Camera> camera) {
    double x, y, width, height;

    // calculando coordenadas virtuais
    _img_data img_data;

    camera->viewport(render_data.window, ObjectInfo {
        static_cast<double>(this->width), static_cast<double>(this->width),
        static_cast<double>(this->x), static_cast<double>(this->y)
    }, x, y, width, height);

    img_data.x = x;
    img_data.y = y;
    img_data.w = width;
    img_data.h = height;

    // criando nova imagem caso não exista
    if (!SDL_Image::exists(render_data.collection, this->name)) {
        SDL_Image::loadImage(render_data.collection, this->name, render_data.window, this->file);
    }

    SDL_Image::render(render_data, this->name, &img_data);
}
