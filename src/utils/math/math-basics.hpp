/*
    Definições matemáticas básicas
*/

#pragma once

#include <cmath>

// função para mudança de faixa
inline double map(double v, double from_min, double from_max, double to_min, double to_max) {
    double v_percentage = (v - from_min) / (from_max - from_min);
    return v_percentage * (to_max - to_min) + to_min;
}

// função para calcular distância
inline double distance(double x1, double y1, double x2, double y2) {
    double distX = abs(x1 - x2);
    double distY = abs(y1 - y2);

    return sqrt(distX * distX + distY * distY);
}
