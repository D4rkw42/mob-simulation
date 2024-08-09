/*
    Definições para geração/renderização de terreno
*/

#include "terrain.hpp"

#include <fstream>

#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

//

const unsigned int TILE_SIZE = 32; // tamanho real de cada tile no mundo

// auxilia no sorteio do bioma
struct BiomeInfo {
    std::string name; // nome do bioma
    int factor; // fator de sorteio
};

// auxilia no sorteio de bloco
struct TileInfo {
    std::string name;
    int factor;
    json variations;
};

void generateTerrain(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera, std::array<std::shared_ptr<Tile>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION>& _tiles) {
    // obtendo as configurações de bioma
    std::ifstream world_config(WORLD_CONFIG_FILE);
    json biome_config = json::parse(world_config)["biomes"];

    // lista de biomas
    json biomes_list = biome_config["list"];
    BiomeInfo biomes[biomes_list.size()];

    // nome de cada bioma
    for (int b = 0; b < biomes_list.size(); ++b) {
        std::string name = biomes_list[b];
        int factor = biome_config[name]["factor"];

        // alocando as informações sobre bioma
        biomes[b] = BiomeInfo {name, factor};
    }

    // calculando posição de cada tile

    // distância de renderização atual
    double dist_horiz, dist_vert;
    camera->getRenderDistance(window, dist_horiz, dist_vert);

    int n_horiz_tiles = dist_horiz / TILE_SIZE;
    int n_vert_tiles = dist_vert / TILE_SIZE;

    if (n_horiz_tiles > MAX_HORIZONTAL_RENDERIZATION) {
        n_horiz_tiles = MAX_HORIZONTAL_RENDERIZATION;
    }

    if (n_vert_tiles > MAX_VERTICAL_RENDERIZATION) {
        n_vert_tiles = MAX_VERTICAL_RENDERIZATION;
    }

    std::cout << "hor: " << n_horiz_tiles << "\n";
    std::cout << "ver: " << n_vert_tiles << "\n";

    // zerando lista para nova geração
    _tiles.fill(nullptr);

    // posição de referência para a geração
    int center_x = static_cast<int>(camera->x) - static_cast<int>(camera->x) % TILE_SIZE;
    int center_y = static_cast<int>(camera->y) - static_cast<int>(camera->y) % TILE_SIZE;

    // posições iniciais e finais de geração
    int start_x = center_x - TILE_SIZE * n_horiz_tiles / 2;
    int start_y = center_y - TILE_SIZE * n_vert_tiles / 2;

    int final_x = center_x + TILE_SIZE * n_horiz_tiles / 2;
    int final_y = center_y + TILE_SIZE * n_vert_tiles / 2;

    // id para alocação na memória
    int id = 0;

    // obtendo cada posição
    for (int x = start_x; x < final_x; x += TILE_SIZE) {
        for (int y = start_y; y < final_y; y += TILE_SIZE) {
            // lógica de geração de mundo

            double biome_selector = perlin.octave2D_01(x, y, 10); // número referente à seleção de bioma
            double b_discriminant = biome_selector * 1000;

            // descobrindo qual bioma foi selecionado para o esquema

            int biome_selected = 0;

            for (int i = 0; i < biomes_list.size(); ++i) {
                // o bioma selecionado terá prioridade se estiver dentro da faixa e for o maior possível
                if (biomes[i].factor > biomes[biome_selected].factor && biomes[i].factor <= b_discriminant) {
                    biome_selected = i;
                }
                // caso nenhum seja escolhido, será o bioma 0
            }

            // nome do bioma selecionado
            std::string biome_name = biomes[biome_selected].name;

            // descobrindo o bloco que será gerado

            // alocando os tipos de tiles do bioma
            json tile_list = biome_config[biome_name]["tiles"];
            TileInfo tiles[tile_list.size()];

            for (int t = 0; t < tile_list.size(); ++t) {
                std::string name = tile_list[t];
                int factor = biome_config[biome_name][name]["factor"];
                json variations = biome_config[biome_name][name]["variations"];

                // alocando informações sobre o tile
                tiles[t] = TileInfo {name, factor, variations};
            }

            double tile_selector = perlin.octave3D_01(x, y, static_cast<double>(biome_config[biome_name]["random-factor"]), 10);
            double t_discriminant = tile_selector * 1000;

            // descobrindo qual bioma foi selecionado para o esquema

            int tile_selected = 0;

            for (int i = 0; i < tile_list.size(); ++i) {
                // o bioma selecionado terá prioridade se estiver dentro da faixa e for o maior possível
                if (tiles[i].factor > tiles[tile_selected].factor && tiles[i].factor <= t_discriminant) {
                    tile_selected = i;
                }
                // caso nenhum seja escolhido, será o tile 0
            }

            // a incluir: variação!!!! Por enquanto, sempre 1

            // alocando o tile na memória
            std::shared_ptr<Tile> m_tile = std::make_shared<Tile>(tiles[tile_selected].name, biomes[biome_selected].name, 1, x, y, TILE_SIZE);
            Tile::loadTexture(window, m_tile); // carregando textura do tile

            _tiles[id++] = m_tile;
            std::cout << id << "\n";

        }
    }

}

void renderTerrain(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera, std::array<std::shared_ptr<Tile>, MAX_HORIZONTAL_RENDERIZATION * MAX_VERTICAL_RENDERIZATION> tiles) {
    for (auto tile : tiles) {
        if (tile != nullptr) {
            tile->render(window, camera);
        }
    }
}