/*
    Define todos os comportamentos do mob lobo
*/

#include "wolf.hpp"

// cadastrando wolf
Wolf::Wolf(int x, int y) : Entity(
    ENTITY_TYPE::WOLF,
    Entity::ReadEntityInfo(ENTITY_TYPE::WOLF),
    x, y
) {}

void Wolf::update(int elapsedTime) {
    // atualização de animações
    this->animation.load(elapsedTime);

    // atualização de movimento
    move();

    // ações conforme estado

    if (this->state == "idle") {
        this->velX = 0;
        this->velY = 0;
    }
}

void Wolf::render(std::shared_ptr<Window> window) {
    // atualização de animações
    updateAnimations();
    this->animation.render(window, this->x, this->y);
}
