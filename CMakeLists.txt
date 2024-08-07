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

set(PERLIN_NOISE_DIR -I "C:/Program Files/Mingw/include/perlin-noise/include")

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    ${SDL2_INCLUDE_DIRS})

add_compile_options(${PERLIN_NOISE_DIR})

# getting source files

# main root
file(GLOB DIR_SRC "src/*.cpp")

# config root
file(GLOB DIR_CONFIG "src/config/*.cpp")
file(GLOB DIR_CONFIG_SDL2 "src/config/sdl2/*.cpp")
file(GLOB DIR_CONFIG_SDL2_GRAPHICS "src/config/sdl2/graphics/*.cpp")

# app root
file(GLOB DIR_APP "src/app/*.cpp")

# utilities root
file(GLOB DIR_UTILS "src/utils/*.cpp")
file(GLOB DIR_UTILS_EVENTS "src/utils/events/*.cpp")
file(GLOB DIR_UTILS_WORLD "src/utils/world/*.cpp")
file(GLOB DIR_UTILS_RENDER "src/utils/render/*.cpp")

# world root
file(GLOB DIR_WORLD_GEN "src/world/gen/*.cpp")
file(GLOB DIR_WORLD_GEN_DEFS "src/world/gen/defs/*.cpp")
file(GLOB DIR_WORLD_ENTITY "src/world/entity/*.cpp")
file(GLOB DIR_WORLD_MOBS "src/world/entity/mobs/*.cpp")

# building project

add_executable(
    mob-simulation
    ${DIR_SRC}

    ${DIR_CONFIG}
    ${DIR_CONFIG_SDL2}
    ${DIR_CONFIG_SDL2_GRAPHICS}

    ${DIR_APP}

    ${DIR_UTILS}
    ${DIR_UTILS_EVENTS}
    ${DIR_UTILS_WORLD}
    ${DIR_UTILS_RENDER}

    ${DIR_WORLD_GEN}
    ${DIR_WORLD_GEN_DEFS}
    ${DIR_WORLD_ENTITY}
    ${DIR_WORLD_MOBS})

# linking external libraries

target_link_libraries(
    mob-simulation PRIVATE

    ${SDL2_LIBRARIES}
    SDL2_image::SDL2_image
    nlohmann_json::nlohmann_json)
