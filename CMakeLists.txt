cmake_minimum_required(VERSION 3.29.7)

project(
    mob-simulation
    VERSION 1.0
    DESCRIPTION "Simulação de multidões feita em C++ e SDL2"
    HOMEPAGE_URL "https://github.com/D4rkw42/mob-simulation"
    LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_ROOT}/Modules/SDL2")
find_package(SDL2 CONFIG REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
# include_directories("${CMAKE_ROOT}/Modules/SDL2/include")

add_executable(mob-simulation src/main.cpp)
target_link_libraries(mob-simulation ${SDL2_LIBRARIES})