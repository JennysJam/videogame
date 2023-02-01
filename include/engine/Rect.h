#ifndef GAME_INCLUDE_SAMPLE_H
#define GAME_INCLUDE_SAMPLE_H

#include <SDL.h>
#include <SDL_rect.h>

namespace engine {

class Rect final {
public:
    friend auto operator==(Rect lhs, Rect rhs) noexcept -> bool;

    Rect() {
        _rect = {0, 0, 0, 0};
    }
    Rect(SDL_Rect rect) noexcept {
        _rect = rect;
    }

    operator SDL_Rect() noexcept {
        return _rect;
    }

private:
    SDL_Rect _rect;
};

auto operator==(Rect lhs, Rect rhs) noexcept -> bool {
    return SDL_RectEquals(&lhs._rect, &rhs._rect);
}

auto operator!=(Rect lhs, Rect rhs) noexcept -> bool {
    return !(lhs == rhs);
}

} // end namespace engine


#endif // GAME_INCLUDE_RECT_H
