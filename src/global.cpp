/*
    Variáveis e definições globais
*/

#include "global.hpp"

// definições gerais
std::shared_ptr<Window> window;

// world variables
std::array<std::shared_ptr<Entity>, MAX_MOBS_SPAWNED> mob_list;
