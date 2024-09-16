/*
    Definições gerais para renderização da flora
*/

#include "flora.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#include "global.hpp"

#include "utils/math/math-basics.hpp"


using Noise = FastNoiseLite;
using json = nlohmann::json;

//

void generateFlora(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera, WorldPositionsRef worldPosRef, PlantList& _plants, TileList tiles) {
    // configuração das opções de ruído
    std::ifstream config_file("assets/config.json");
    json config = json::parse(config_file)["world"]["gen"]["plant"];

    // informações sobre os biomas
    std::ifstream biome_config_file("assets/world.json");
    json biome_config = json::parse(biome_config_file)["biomes"];
    
    // configuração do voronoi noise
    voronoi_noise.SetFractalType(Noise::FractalType::FractalType_PingPong);
    voronoi_noise.SetCellularDistanceFunction(Noise::CellularDistanceFunction::CellularDistanceFunction_EuclideanSq);
    voronoi_noise.SetCellularReturnType(Noise::CellularReturnType::CellularReturnType_CellValue);
    voronoi_noise.SetDomainWarpType(Noise::DomainWarpType::DomainWarpType_OpenSimplex2Reduced);

    voronoi_noise.SetFrequency(config["area"]["frequency"]);
    voronoi_noise.SetFractalOctaves(config["area"]["octaves"]);
    voronoi_noise.SetDomainWarpAmp(config["area"]["amplitude"]);
    voronoi_noise.SetCellularJitter(config["area"]["jitter"]);
    voronoi_noise.SetFractalLacunarity(config["area"]["lacunarity"]);
    voronoi_noise.SetFractalGain(config["area"]["gain"]);

    // configuração do perlin noise
    perlin_noise.SetFractalType(Noise::FractalType::FractalType_FBm);

    perlin_noise.SetFrequency(config["tile"]["frequency"]);
    perlin_noise.SetFractalOctaves(config["tile"]["octaves"]);
    perlin_noise.SetFractalLacunarity(config["tile"]["lacunarity"]);
    perlin_noise.SetFractalGain(config["tile"]["gain"]);

    // limpando as plantas já geradas
    _plants.fill(nullptr);

    // fazendo geração procedural de plantas
    for (int i = 0; i < worldPosRef.maxIDGenerated; ++i) {
        double x = worldPosRef.worldPositions[i].x;
        double y = worldPosRef.worldPositions[i].y;

        // nome do bioma do bloco especificado
        std::string biome = tiles[i]->biome;
        json biome_plants = biome_config[biome]["plants"];

        // não gera caso o bioma nãi tenha plantas
        if (biome_plants.size() == 0) {
            continue;
        }

        // obtendo valores aleatórios
        double voronoi = voronoi_noise.GetNoise(x, y);
        double perlin = perlin_noise.GetNoise(x, y);

        // ajustando a faixa de valores
        voronoi = map(voronoi, -1, 1, 0, 1);
        perlin = map(perlin, -1, 1, 0, 1);

        // geração bloqueada localmente
        if (perlin < 0.55f || static_cast<int>(perlin * 100) % 2 == 0 || static_cast<int>(perlin * 100) % 7 == 0) {
            continue;
        }

        // remapping
        perlin = map(perlin, 0.55f, 1, 0, 1);

        if (voronoi < 0.3f) { // gera apenas um tipo de planta
            voronoi = map(voronoi, 0, 0.3f, 0, 1);

            int selected_plant = biome_plants.size() * voronoi - 1;

            if (selected_plant < 0) {
                selected_plant = 0;
            }

            std::string m_plant = biome_plants[selected_plant];
            _plants[i] = std::make_shared<Plant>(m_plant, x, y);
        } else if (voronoi < 0.6f) { // gera todos os tipos de planta
            int selected_plant = biome_plants.size() * perlin - 1;

            if (selected_plant < 0) {
                selected_plant = 0;
            }

            std::string m_plant = biome_plants[selected_plant];
            _plants[i] = std::make_shared<Plant>(m_plant, x, y);
        }
    }
}

void renderFlora(RenderData render_data, std::shared_ptr<Camera> camera, PlantList plants) {
    for (auto plant : plants) {
        if (plant == nullptr) {
            continue;
        }
        
        plant->render(render_data, camera);
    }
}
