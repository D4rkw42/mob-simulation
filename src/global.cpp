/*
    Variáveis e definições globais
*/

#include "global.hpp"

// definições gerais
std::shared_ptr<Window> window;

// para gestão de eventos
Mouse mouse = {
    0, 0,
    Mouse_Info {false, 0, 0}, // right
    Mouse_Info {false, 0, 0} // left
};

// world variables
std::shared_ptr<Camera> camera;
std::array<std::shared_ptr<Entity>, MAX_MOBS_SPAWNED> mob_list;
