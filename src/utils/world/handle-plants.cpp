/*
    Definições para manipulação de plantas
*/

#include "handle-plants.hpp"

// cria uma planta no mapa
void createNewPlant(std::array<std::shared_ptr<Plant>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> &plants, std::string type, int x, int y) {
    std::shared_ptr<Plant> m_plant = std::make_shared<Plant>(type, x, y);

    for (int i = 0; i < plants.size(); ++i) {
        if (plants[i] == nullptr) {
            plants[i] = m_plant;
            break;
        }
    }
}
