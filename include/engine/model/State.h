#ifndef GAME_INCLUDE_ENGINE_MODEL_H
#define GAME_INCLUDE_ENGINE_MODEL_H

#include <SDL_events.h>
#include <cstdbool>


namespace engine {
namespace model {

class GameState;

/// @brief Abstract base class for variant of statemachine
class State {
public:
    virtual ~State() = default;
    
    virtual auto react(SDL_Event& eventum) -> bool = 0;
    virtual void update(double dt) = 0;
    virtual void render() = 0;
};

}
} // end namespace engine

#endif