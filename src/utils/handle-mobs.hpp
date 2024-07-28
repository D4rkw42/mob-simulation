/*
    Funções que auxiliam na gestão de mobs
*/

#pragma once

#include <array>

#include "config.hpp"
#include "entity/entity.hpp"

// criação dinâmica de mobs
template <class MobType>
void spawnNewMob(std::array<std::shared_ptr<Entity>, MAX_MOBS_SPAWNED>& mob_list, int x, int y) {
    std::shared_ptr<Entity> my_entity = createEntity<MobType>(x, y); // criando a entidade

    for (int i = 0; i < MAX_MOBS_SPAWNED; ++i) {
        if (mob_list[i] == nullptr) { // procura pela primeira lacuna vazia
            mob_list[i] = my_entity;
            break;
        }
    }
}
