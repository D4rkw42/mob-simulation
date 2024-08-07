/*
    Define todos os comportamentos do mob lobo
*/

#pragma once

#include "world/entity/entity.hpp"
#include "utils/world/camera.hpp"

class Wolf : public Entity {
    public:
        Wolf(int x, int y);

        void update(int elapsedTime);
        void render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera);
};
