#ifndef GAME_INCLUDE_MODEL_ENTITY_H
#define GAME_INCLUDE_MODEL_ENTITY_H

#include "engine/model/Game.h"

namespace engine {
namespace model {

class Entity {
public:
    Entity() = default;
    virtual ~Entity() noexcept = default;

    virtual void init(Game& ctx) = 0;
    virtual void update(Game& ctx, double dt) = 0;
    virtual void render(Game& ctx) = 0;
};

}
}

#endif