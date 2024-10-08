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

void Wolf::update(int deltatime) {
    // atualização de animações
    this->animation.load(deltatime);

    // atualização de movimento
    move();

    // atualizando dados da hitbox
    updateHitbox();

    // ações conforme estado

    if (this->state == "idle") {
        this->velX = 0;
        this->velY = 0;
    } else if (this->state == "chasing") {
        followDestiny();
    }
}

void Wolf::render(RenderData render_data, std::shared_ptr<Camera> camera) {
    // atualização de quadros
    updateAnimations();
    this->animation.render(render_data, camera, this->x, this->y);
}
