cmake_minimum_required(VERSION 3.29.7)

project(
    mob-simulation
    VERSION 1.0
    DESCRIPTION "Simulação de multidões feita em C++ e SDL2"
    HOMEPAGE_URL "https://github.com/D4rkw42/mob-simulation"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# dependencies

find_package(SDL2 CONFIG REQUIRED) # SDL.h library
find_package(SDL2_image CONFIG REQUIRED) # SDL_image.h library
find_package(nlohmann_json CONFIG REQUIRED) # nlohmann::json library

# header definitions

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    ${SDL2_INCLUDE_DIRS})

# getting source files

file(GLOB DIR_SRC "src/*.cpp")
file(GLOB DIR_SRC_UTILS "src/utils/*.cpp")
file(GLOB DIR_SRC_ENTITY "src/entity/*.cpp")
file(GLOB DIR_SRC_ENTITY_MOBS "src/entity/mobs/*.cpp")
file(GLOB DIR_SRC_SDL2 "src/sdl2/*.cpp")
file(GLOB DIR_SRC_SDL2_GRAPHICS "src/sdl2/graphics/*.cpp")

# building project

add_executable(
    mob-simulation

    ${DIR_SRC}
    ${DIR_SRC_UTILS}
    ${DIR_SRC_ENTITY}
    ${DIR_SRC_ENTITY_MOBS}
    ${DIR_SRC_SDL2}
    ${DIR_SRC_SDL2_GRAPHICS})

# linking external libraries

target_link_libraries(
    mob-simulation PRIVATE

    ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image
    nlohmann_json::nlohmann_json)
