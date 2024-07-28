/*
    Definição básica de entidade
*/

#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "utils/animation.hpp"
#include "utils/camera.hpp"

#include "sdl2/graphics/window.hpp"

// info para as informações carregadas
typedef nlohmann::json EntityInfo;

// definição de tipo (entidades)
enum class ENTITY_TYPE {WOLF};

// definição de entity_data para guardar informações customizadas
struct EntityData {
    std::string value; // valor
    std::string value_type; // tipo do valor
};

// localização dos dados de uma entidade
extern const char* ENTITY_CONFIG_FILE; // dados básicos
extern const char* ENTITY_SPRITE_PATH; // sprites

// classe básica para entidades
class Entity {
    public:
        double x, y, velX, velY;
        
        Entity(ENTITY_TYPE type, EntityInfo info, int x, int y);
        virtual ~Entity() = default;

        // faz a leitura dos dados de uma entidade
        static EntityInfo ReadEntityInfo(ENTITY_TYPE entity_type);
  
        // funções compartilhadas de operação

        virtual void update(int elapsedTime);
        virtual void render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera);

        void invalidate(void); // torna a entidade inválida

        // funções compartilhadas que mudam o estado
        void idle(void); // o estado da entidade se torna "idle"
        void walk(void); // o estado da entidade se torna "walking"
        void run(void); // o estado da entidade se torna "running"

        void setState(std::string state); // muda o estado da entidade para a selecionada

    protected:
        Animation animation;
        std::unordered_map<std::string, EntityData> data;

        ENTITY_TYPE type;
        std::string state; // estado da entidade
        std::string _last_state; // estado anterior

        bool isValid; // marca de uma entidade é válida ou não. Caso não seja, o sistema a apaga

        int width, height;

        nlohmann::json animation_info; // dados para animação

        // funções compartilhadas

         /*
         *
         * move muda altomaticamente a posição de uma entidade
         * essa função deve ser chamada dentro de Entity::update(...)
         * 
         */
        void move(void); // move a entidade

        /*
         *
         * updateAnimations atualiza automaticamente as definições de animação
         * essa função deve ser chamada dentro de Entity::render(...) como primeira chamada
         * 
         */
        void updateAnimations(void);
};

// criação dinâmica de entidades

template <class MobType>
std::shared_ptr<Entity> createEntity(int x, int y) {
    std::shared_ptr<MobType> entity = std::make_shared<MobType>(x, y);
    return std::dynamic_pointer_cast<Entity>(entity);
}
