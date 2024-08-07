/*
    Define todos os comportamentos do mob lobo
*/

#include "wolf.hpp"

// cadastrando wolf
Wolf::Wolf(int x, int y) : Entity(
    ENTITY_TYPE::WOLF,
    Entity::ReadEntityInfo(ENTITY_TYPE::WOLF),
    x, y
) {setState("chasing");}

void Wolf::update(int elapsedTime) {
    // atualização de animações
    this->animation.load(elapsedTime);

    // atualização de movimento
    move();

    // ações conforme estado

    if (this->state == "idle") {
        this->velX = 0;
        this->velY = 0;
    } else if (this->state == "chasing") {
        this->velX = -0.1;
    }
}

void Wolf::render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera) {
    // atualização de animações
    updateAnimations();
    this->animation.render(window, camera, this->x, this->y);
}
