/*
    Variáveis e definições globais
*/

#pragma once

#include <memory>

#include "sdl2/graphics/window.hpp"

// configuração
extern const char* APPLICATION_NAME;

extern const unsigned short FRAME_RATE;

// definições gerais
extern std::shared_ptr<Window> window;
