/*
    Define todos os comportamentos do mob lobo
*/

#pragma once

#include "world/entity/entity.hpp"
#include "utils/world/camera.hpp"

class Wolf : public Entity {
    public:
        Wolf(int x, int y);

        void update(int deltatime);
        void render(RenderData render_data, std::shared_ptr<Camera> camera);
};
