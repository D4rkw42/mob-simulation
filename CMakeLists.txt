cmake_minimum_required(VERSION 3.29.7)

project(
    mob-simulation
    VERSION 1.0
    DESCRIPTION "Simulação de multidões feita em C++ e SDL2"
    HOMEPAGE_URL "https://github.com/D4rkw42/mob-simulation"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    ${SDL2_INCLUDE_DIRS})

add_executable(
    mob-simulation

    src/main.cpp
    src/global.cpp
    src/application.cpp
    src/event-handler.cpp
    
    src/utils/exception.cpp
    src/utils/animation.cpp

    src/sdl2/config.cpp
    src/sdl2/graphics/window.cpp)

target_link_libraries(
    mob-simulation

    ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image)
