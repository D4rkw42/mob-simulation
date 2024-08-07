/*
    Definição de tile
*/

#pragma once

#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "config/sdl2/graphics/window.hpp"
#include "utils/world/camera.hpp"

// definições
extern const char* TILE_IMG_PATH; // caminho para as imagens de cada tile

class Tile {
    public:
        int x, y, width;

        std::string name, biome;
        int variation;

        Tile(std::string name, std::string biome, int variation, int x, int y, int width);
        ~Tile();

        void render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera);
        static void loadTexture(std::shared_ptr<Window> window, std::shared_ptr<Tile> tile); // carrega as texturas antes do primeiro uso

    private:
        SDL_Surface* surface;
        SDL_Texture* texture;
};

