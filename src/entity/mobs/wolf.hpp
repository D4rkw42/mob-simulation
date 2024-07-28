/*
    Define todos os comportamentos do mob lobo
*/

#pragma once

#include "entity/entity.hpp"

class Wolf : public Entity {
    public:
        Wolf(int x, int y);

        void update(int elapsedTime);
        void render(std::shared_ptr<Window> window);
};
