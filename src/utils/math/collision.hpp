/*
    Definições para cálculo de colisão
*/

#pragma once

#include <cmath>

// caixa de colisão
struct Hitbox {
    int x, y, width, height;
};

// colisão no eixo x
inline bool isCollidingX(Hitbox obj1, Hitbox obj2) {
    double distX = abs(obj1.x - obj2.x);
    return distX <= (obj1.width / 2 + obj2.width / 2);
}

// colisão no eixo y
inline bool isCollidingY(Hitbox obj1, Hitbox obj2) {
    double distY = abs(obj1.y - obj2.y);
    return distY <= (obj1.height / 2 + obj2.height / 2);
}

// verifica se houve colisão entre dois objetos
inline bool isColliding(Hitbox obj1, Hitbox obj2) {
    return isCollidingX(obj1, obj2) && isCollidingY(obj1, obj2);
}
