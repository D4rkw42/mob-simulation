/*
    Apenas definições que guardam o estado do mouse
*/

#pragma once

// informações de botões específicos
struct Mouse_Info {
    bool hold; // se está segurando
    int hold_x, hold_y; // posição que começou a segurar
};

// definições de mouse
struct Mouse {
    int x, y; // posição do mouse em tempo real
    Mouse_Info right;
    Mouse_Info left;
};
