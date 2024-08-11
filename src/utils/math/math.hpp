/*
    Definições matemáticas
    As funções no arquivo principal são definições matemáticas básicas
*/

#pragma once

// função para mudança de faixa
inline double map(double v, double from_min, double from_max, double to_min, double to_max) {
    double v_percentage = (v - from_min) / (from_max - from_min);
    return v_percentage * (to_max - to_min) + to_min;
}
