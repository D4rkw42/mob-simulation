/*
    Definição de tile
*/

#include "tile.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

// definições
const char* TILE_IMG_PATH = "assets/images/world/terrain/";

Tile::Tile(std::string name, std::string biome, int variation, int x, int y, int width) : name(name), biome(biome), variation(variation), x(x), y(y), width(width) {}
Tile::~Tile() {
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(this->surface);
}

void Tile::render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera) {
    double x, y, width, height;

    // calculando coordenadas virtuais
    SDL_Rect rect;

    camera->viewport(window, ObjectInfo {
        static_cast<double>(this->width), static_cast<double>(this->width),
        static_cast<double>(this->x), static_cast<double>(this->y)
    }, x, y, width, height);

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    // renderizando
    SDL_RenderCopy(window->renderer, this->texture, nullptr, &rect);
}

//

void Tile::loadTexture(std::shared_ptr<Window> window, std::shared_ptr<Tile> tile) {
    std::string img_path = std::string(TILE_IMG_PATH) + tile->name + "/" + tile->name + std::to_string(tile->variation) + ".png";
    
    SDL_Surface* surface = IMG_Load(img_path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, surface);

    tile->surface = surface;
    tile->texture = texture;
}
