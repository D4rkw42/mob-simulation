/*
    Definições para geração/renderização de terreno
*/

#include "terrain.hpp"

#include <fstream>

#include <nlohmann/json.hpp>
#include <FastNoise/FastNoiseLite.h>
#include <exception>

#include "global.hpp"

#include "utils/math/math-basics.hpp"

using json = nlohmann::json;
using Noise = FastNoiseLite;

//

// auxilia no sorteio do bioma
struct BiomeInfo {
    std::string name; // nome do bioma
    double factor; // fator de sorteio
};

// auxilia no sorteio de bloco
struct TileInfo {
    std::string name;
    double factor;
    json variations;
};

void generateTerrain(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera, WorldPositionsRef worldPosRef, TileList& _tiles) {
    // configurações da aplicação
    json biome = config["world"]["gen"]["biome"];
    json tiles = config["world"]["gen"]["tile"];

    // configurando noises
    
    // voronoi_noise (para biomas)
    voronoi_noise.SetCellularDistanceFunction(Noise::CellularDistanceFunction::CellularDistanceFunction_Hybrid);
    voronoi_noise.SetDomainWarpType(Noise::DomainWarpType::DomainWarpType_OpenSimplex2);
    voronoi_noise.SetFractalType(Noise::FractalType::FractalType_PingPong);
    voronoi_noise.SetCellularReturnType(Noise::CellularReturnType::CellularReturnType_CellValue);

    voronoi_noise.SetFractalOctaves(biome["octaves"]);
    voronoi_noise.SetFrequency(biome["frequency"]);
    voronoi_noise.SetCellularJitter(biome["jitter"]);
    voronoi_noise.SetDomainWarpAmp(biome["amplitude"]);
    voronoi_noise.SetFractalLacunarity(biome["lacunarity"]);
    voronoi_noise.SetFractalGain(biome["gain"]);
    
    // perlin_noise (para biomas)
    perlin_noise.SetFractalType(Noise::FractalType::FractalType_FBm);
    
    perlin_noise.SetFractalOctaves(tiles["octaves"]);
    perlin_noise.SetFractalLacunarity(tiles["lacunarity"]);
    perlin_noise.SetFractalGain(tiles["gain"]);
    perlin_noise.SetFrequency(tiles["frequency"]);

    // obtendo as configurações de bioma
    std::ifstream world_config(WORLD_CONFIG_FILE);
    json biome_config = json::parse(world_config)["biomes"];

    // lista de biomas
    json biomes_list = biome_config["list"];
    BiomeInfo biomes[biomes_list.size()];

    // nome de cada bioma
    for (int b = 0; b < biomes_list.size(); ++b) {
        std::string name = biomes_list[b];
        double factor = biome_config[name]["factor"];

        // alocando as informações sobre bioma
        biomes[b] = BiomeInfo {name, factor};
    }

    // zerando lista para nova geração
    _tiles.fill(nullptr);

    // obtendo cada posição
    for (int id = 0; id < worldPosRef.maxIDGenerated; ++id) {
        int x = worldPosRef.worldPositions[id].x;
        int y = worldPosRef.worldPositions[id].y;

        // lógica de geração de mundo

        // número aleatório para reger o mundo
        double noise_x_b = x / TILE_SIZE * static_cast<double>(biome["mod"]);
        double noise_y_b = y / TILE_SIZE * static_cast<double>(biome["mod"]);

        double noise_x_t = x / TILE_SIZE * static_cast<double>(tiles["mod"]);
        double noise_y_t = y / TILE_SIZE * static_cast<double>(tiles["mod"]);

        double voronoi = voronoi_noise.GetNoise(noise_x_b, noise_y_b);
        double perlin = perlin_noise.GetNoise(noise_x_t, noise_y_t);

        voronoi = map(voronoi, -1, 1, 0, 1);
        perlin = map(perlin, -1, 1, 0, 1);

        // descobrindo qual bioma foi selecionado para o esquema
        int biome_selected = 0;
        double b_factor = 1;

        for (int i = 0; i < biomes_list.size(); ++i) {
            if (biomes[i].factor >= voronoi && biomes[i].factor <= b_factor) {
                b_factor = biomes[i].factor;
                biome_selected = i;
            }
        }

        // nome do bioma selecionado
        std::string biome_name = biomes[biome_selected].name;

        // descobrindo o bloco que será gerado

        // alocando os tipos de tiles do bioma
        json tile_list = biome_config[biome_name]["tiles"];
        TileInfo tiles[tile_list.size()];

        for (int t = 0; t < tile_list.size(); ++t) {
            std::string name = tile_list[t];
            double factor = biome_config[biome_name][name]["factor"];
            json variations = biome_config[biome_name][name]["variations"];

            // alocando informações sobre o tile
            tiles[t] = TileInfo {name, factor, variations};
        }


        // descobrindo qual tile foi selecionado para o esquema
        int tile_selected = 0;
        double t_factor = 1;

        for (int i = 0; i < tile_list.size(); ++i) {
            if (tiles[i].factor >= perlin && tiles[i].factor <= t_factor) {
                t_factor = tiles[i].factor;
                tile_selected = i;
            }
        }

        // computando variação de blocos
            
        int n_variations = tiles[tile_selected].variations.size();
        int variation_selected = trunc(perlin * n_variations) - 1;

        // proteção
        if (variation_selected < 0) {
            variation_selected = 0;
        }

        // alocando o tile na memória
        std::shared_ptr<Tile> m_tile = std::make_shared<Tile>(tiles[tile_selected].name, biomes[biome_selected].name, tiles[tile_selected].variations[variation_selected], x, y, TILE_SIZE + 2);

        _tiles[id] = m_tile;
    }
}

void renderTerrain(RenderData render_data, std::shared_ptr<Camera> camera, TileList tiles) {
    for (auto tile : tiles) {
        if (tile == nullptr) {
            break;
        }
        tile->render(render_data, camera);
    }
}
