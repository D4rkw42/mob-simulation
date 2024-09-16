/*
    Definições do algoritmo wavefront
*/

#pragma once

#include <cmath>
#include <vector>
#include <string>

#include "world/world.hpp"

#include "math-basics.hpp"

const int MAX_WAVE_DISTANCE = 100; // dist
const int WAVE_STEP = 5; // px

/*
 * estrutura básica de dados para calcular o wavefront
 *
 * dist = 0 -> node válido
 * dist = -1 -> node inválido
 * dist > 0 -> node já calculado
 * 
 */
struct Node {
    WorldCoord coord;
    int x, y; // apenas em relação a grid
    int dist;
};

// configuração

// tiles inválidos
std::vector<std::string> invalidTiles = {"water"};

// criação dinâmica de nodes
inline Node createNode(int x, int y, int dist = 0) {
    Node m_node;

    m_node.coord = WorldCoord {x, y};
    m_node.dist = dist;

    return m_node;
}

// criar uma grid de nodes para o wavefront
inline std::vector<std::vector<Node>> createWaveFrontGrid(World world, WorldCoord origin, WorldCoord destiny, Hitbox hitbox) { // hitbox serve para verificar se ponto que irá se mover tem espaço
    int dist_x = abs(origin.x - destiny.y);
    int dist_y = abs(origin.y - destiny.y);

    int dist = (dist_x > dist_y)? dist_x : dist_y;

    std::vector<std::vector<Node>> m_nodes;

    // distancia escolhida para a grid
    const int WAVE_DIST = dist / WAVE_STEP;

    // verifica se a distância necessária é muito alta
    if (WAVE_DIST > MAX_WAVE_DISTANCE) {
        return m_nodes; // grid vazia
    }

    // caso origin = destiny
    if (origin.x == destiny.x && origin.y == destiny.y) {
        return m_nodes;
    }

    // criando a grid
    int id_x = 0, id_y = 0; // aux id's

    m_nodes.resize(WAVE_DIST * 2 + 1); // resizing for x

    for (int x = -WAVE_DIST; x <= WAVE_DIST; ++x) {
        m_nodes[id_x].resize(WAVE_DIST * 2 + 1); // resizing for y

        for (int y = -WAVE_DIST; y <= WAVE_DIST; ++y) {
            int node_x = destiny.x + x * WAVE_STEP;
            int node_y = destiny.y + y * WAVE_STEP;

            m_nodes[id_x][id_y] = createNode(node_x, node_y);
            m_nodes[id_x][id_y].x = id_x;
            m_nodes[id_x][id_y].y = id_y;

            // verificando validade do node

            // colisão com plantas
            

            // blocos inválidos
            auto tile = findTile(world.tiles, node_x, node_y);

            if (!tile || std::find(invalidTiles.begin(), invalidTiles.end(), tile->name) == invalidTiles.end()) {
                m_nodes[id_x][id_y].dist = -1;
            }

            id_y++;
        }

        id_x++;
        id_y = 0;
    }

    return m_nodes;
}

inline std::vector<WorldCoord> wavefront(World world, WorldCoord origin, WorldCoord destiny, Hitbox hitbox) {
    auto m_nodes = createWaveFrontGrid(world, origin, destiny, hitbox);
    std::vector<WorldCoord> coords; // coordenadas para chegar ao destino

    //caso não seja possível criar a grid, retorna um vetor de coordenadas vazio
    if (m_nodes.size() == 0) {
        return coords;
    }

    std::vector<Node> discovered, new_discovered;

    // encontrando o node de referência (central - destiny)

    // distancia escolhida para a grid
    const int WAVE_DIST = m_nodes.size();

    int ref_id_x = WAVE_DIST / 2 + 1;
    int ref_id_y = WAVE_DIST / 2 + 1;

    // criando primeiro node (o de referencia)
    discovered.push_back(m_nodes[ref_id_x][ref_id_y]);
    discovered[0].dist = 1;

    // calculando todas as distância do node para o node central

    // direções que serão encontrados novos nodes
    int discover_dirs[4][2] = {
        {0, -1}, // x + 0, y - 1 (node acima)
        {1, 0}, // x + 1, y + 0 (node à direita)
        {0, 1}, // x + 0, y + 1 (node abaixo),
        {-1, 0} // x - 1, y + 0 (node à esquerda)
    };

    int curr_dist = 2; // variável auxiliar para calcular a distância do node de destino

    while (true) {
        // procurando novos nodes a partir dos já descobertos
        for (Node node : discovered) {
            // posição dentro da grid
            int id_x = node.x;
            int id_y = node.y;

            // busca com base nas direções
            for (int i= 0; i < 4; ++i) {
                int dir_x = discover_dirs[i][0];
                int dir_y = discover_dirs[i][1];

                // buscando node que não existe na grid
                if (id_x + dir_x < 0 || id_x + dir_x > WAVE_DIST || id_y + dir_y < 0 || id_y + dir_y > WAVE_DIST) {
                    continue;
                }

                // node canditato
                Node& candidate = m_nodes[id_x + dir_x][id_y + dir_y];

                // node inválido ou já calculado
                if (candidate.dist == -1 || candidate.dist > 0) {
                    continue;
                }

                candidate.dist = curr_dist;
                new_discovered.push_back(candidate);
            }
        }

        // condição para toda grid calculada
        if (new_discovered.size() == 0) {
            break;
        }

        discovered = new_discovered;
        new_discovered.clear();

        curr_dist++;
    }

    // traçando o caminho do wavefront
    int path_dirs[8][2] = {
        {0, -1}, // x + 0, y - 1 (acima)
        {1, -1}, // x + 1, y -1 (canto superior-direito)
        {1, 0}, // x + 1, y + 0 (à direita)
        {1, 1}, // x + 1, y + 1 (canto inferior-direito)
        {0, 1}, // x + 0, y + 1 (abaixo)
        {-1, 1}, // x -1 , y + 1 (canto inferior-esquerdo)
        {-1, 0}, // x - 1, y + 0 (à esquerda)
        {-1, -1} // x - 1, y -1 (canto superior-esquerdo)
    };

    Node ref_node; // node de referência para encontrar o caminho

    // encontrando o ponto de origem dentro da grid
    int aux_dist = 9999; // aux para encontrar o node mais próximo da origem

    for (auto x = 0; x < WAVE_DIST; ++x) {
        for (auto y = 0; y < WAVE_DIST; ++y) {
            Node node = m_nodes[x][y];
            int dist = distance(origin.x, origin.y, node.coord.x, node.coord.y);

            if (dist < aux_dist) {
                aux_dist = dist;
                ref_node = node;
            }
        }
    }

    // traçando caminho
    while (true) {
        Node new_ref_node;
        int dist = MAX_WAVE_DISTANCE;

        for (int i = 0; i < 8; ++i) {
            int dir_x = path_dirs[i][0];
            int dir_y = path_dirs[i][1];

            // buscando node que não existe na grid
            if (ref_node.x + dir_x < 0 || ref_node.x + dir_x > WAVE_DIST || ref_node.y + dir_y < 0 || ref_node.y + dir_y > WAVE_DIST) {
                continue;
            }

            Node candidate = m_nodes[ref_node.x + dir_x][ref_node.y + dir_y];

            if (candidate.dist < dist) {
                new_ref_node = candidate;
                dist = candidate.dist;
            }
        }

        coords.push_back(new_ref_node.coord);

        // encontrado o último ponto que é o destino
        if (new_ref_node.coord.x == destiny.x && new_ref_node.coord.y == destiny.y) {
            break;
        }

        ref_node = new_ref_node;
        dist = MAX_WAVE_DISTANCE;
    }

    return coords;
}
