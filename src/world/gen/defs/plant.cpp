/*
    Definições gerais para planta
*/

#include "plant.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

//

const char* PLANT_CONFIG_FILE = "assets/plants.json";
const char* PLANT_ASSETS_PATH = "assets/images/world/flora/";

// criação de uma planta
Plant::Plant(std::string type, int x, int y) : type(type), x(x), y(y) {
    std::ifstream plant_config(PLANT_CONFIG_FILE);
    json config = json::parse(plant_config)[type];

    //

    // desvio para desenho
    this->offset_x = config["offset"]["x"];
    this->offset_y = config["offset"]["y"];

    // tamanhos
    this->width = config["width"];
    this->height = config["height"];

    this->hitbox = Hitbox {x, y, this->width, this->height};

    this->scale = config["scale"];
}

void Plant::render(RenderData render_data, std::shared_ptr<Camera> camera) {
    double x, y, width, height;

    // transformações necessárias para ajuste
    double scaled_width = this->width * this->scale;
    double scaled_height = this->height * this->scale;

    double changed_x = this->x + this->offset_x;
    double changed_y = this->y + this->offset_y;

    // calculando tamanho e posições reais no mundo
    camera->viewport(render_data.window, ObjectInfo {
        static_cast<double>(scaled_width), static_cast<double>(scaled_height),
        static_cast<double>(changed_x), static_cast<double>(changed_y)
    }, x, y, width, height);

    // desenhando objeto
    std::string file = std::string(PLANT_ASSETS_PATH) + this->type + ".png";
    _img_data img_data;

    img_data.x = x;
    img_data.y = y;
    
    img_data.w = width;
    img_data.h = height;

    if (!SDL_Image::exists(render_data.collection, this->type)) {
        SDL_Image::loadImage(render_data.collection, this->type, render_data.window, file);
    }

    SDL_Image::render(render_data, this->type, &img_data);
}
