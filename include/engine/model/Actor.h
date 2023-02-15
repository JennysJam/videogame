#ifndef GAME_INCLUDE_MODEL_ACTOR_H
#define GAME_INCLUDE_MODEL_ACTOR_H

#include "engine/model/Game.h"
#include "engine/model/Entity.h"

#include <glm/vec2.hpp>
#include <typeinfo>

namespace engine {
namespace model {

    // forward declare
    class ActorType;

    /// @brief Class that represents primary type of NPC/actively interacting entity in the game
    class Actor final : public Entity {
    public:
        Actor(ActorType& actortype, int health);
        virtual ~Actor();
        
        void init(Game&) override;
        void update(Game& game, double dt) override;
        void render(Game& game) override;

        double x() const;
        Actor& x(double newx);
        
        double y() const;
        Actor& y(double newy);

        glm::dvec2 pos() const;
        Actor& pos(glm::dvec2 newvec);
        Actor& pos(double nx, double ny);

        int health() const;
        Actor& health(int new_health);

    private:
        ActorType* _type;
        glm::dvec2 _pos;
        int _health;
    };

}
}


#endif