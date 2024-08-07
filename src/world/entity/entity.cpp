/*
    Definição básica de entidade
*/

#include "entity.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

// localização dos dados de uma entidade
const char* ENTITY_CONFIG_FILE = "assets/entities.json"; // dados básicos
const char* ENTITY_SPRITE_PATH = "assets/sprites/entity/"; // sprites

// associação entre tipos e seus respectivos nomes
std::unordered_map<ENTITY_TYPE, std::string> ENTITY_TYPE_LIST = {
    {ENTITY_TYPE::WOLF, "wolf"}
};

// classe básica para entidades
Entity::Entity(ENTITY_TYPE type, EntityInfo info, int x, int y) : type(type), state("idle"), x(x), y(y), velX(0), velY(0), isValid(true) {
    for (auto field : info["data"]) {
        std::string field_name = field[0]; // o nome da informação a ser guardada
        EntityData entity_data = {field[1], std::string(field[2])}; // valor da informação + seu tipo

        // alocando
        this->data[field_name] = entity_data;
    }

    // salvando dados
    this->width = info["width"];
    this->height = info["height"];

    // animação é controlada pelo estado
    animation_info = info["animations"];
    updateAnimations(); // primeira atualização necessária para carregar a primeira animação
}

EntityInfo Entity::ReadEntityInfo(ENTITY_TYPE entity_type) {
    // abrindo arquivo com as informações de entidades
    std::ifstream entity_config_file(ENTITY_CONFIG_FILE);

    // carregando os dados na árvore json
    EntityInfo info = json::parse(entity_config_file);

    return info[ENTITY_TYPE_LIST[entity_type]]; // retorna os dados especificados em entity_type
}

// funções compartilhadas

void Entity::move(void) {
    this->x += this->velX;
    this->y += this->velY;
}

void Entity::updateAnimations(void) {
    if (this->_last_state != this->state) { // se o estado mudou, atualiza as animações
        // atualizando os dados da animação
        AnimationInfo a_info = {
            this->width, this->height,
            this->animation_info[this->state]["n_sprites"], // n sprites
            this->animation_info[this->state]["duration"], // duration
            this->animation_info[this->state]["repeat"] // repeat
        };

        // arquivo que contém a animação
        std::string g_path = ENTITY_SPRITE_PATH;
        std::string f_path = this->animation_info[this->state]["spritesheet"];
        std::string file = g_path + f_path;

        this->animation.set(file, a_info);
        this->_last_state = this->state;
    }
}

void Entity::invalidate(void) {
    this->isValid = false;
}

// funções compartilhadas de operação

void Entity::update(int elapsedTime) {}
void Entity::render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera) {}

// funções compartilhadas que mudam o estado

void Entity::setState(std::string state) {
    this->state = state;
}

void Entity::idle(void) {
    setState("idle");
}

void Entity::walk(void)  {
    setState("walking");
}

void Entity::run(void) {
    setState("running");
}
