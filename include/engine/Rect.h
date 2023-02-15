#ifndef GAME_INCLUDE_SAMPLE_H
#define GAME_INCLUDE_SAMPLE_H

#include "engine/Option.h"

#include <SDL.h>
#include <SDL_rect.h>

namespace engine {

/// @brief Object orriented wrapper around SDL_Rect
class Rect final: public SDL_Rect {
public:
    friend auto operator==(Rect lhs, Rect rhs) noexcept -> bool;
    SDL_Rect* as_sdl_rect();
    bool is_empty() const noexcept;
    operator bool() const noexcept;
    bool has_intersect(const Rect& other) const noexcept;
    auto intersect(const Rect& other) -> Option<Rect>;
};

auto operator==(Rect lhs, Rect rhs) noexcept -> bool {
    return SDL_RectEquals(lhs.as_sdl_rect(), rhs.as_sdl_rect());
}

auto operator!=(Rect lhs, Rect rhs) noexcept -> bool {
    return !(lhs == rhs);
}

} // end namespace engine


#endif // GAME_INCLUDE_RECT_H
