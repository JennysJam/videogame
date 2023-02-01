#ifndef GAME_INCLUDE_UTIL_HANDLET_H
#define GAME_INCLUDE_UTIL_HANDLET_H

#include <SDL.h>

namespace engine {
namespace util {

/// @brief A type to be used as a handle
/// @tparam T 
template<typename T>
struct HandleT final {
    std::int32_t value;
};


} // end namespace util
} // end namespace engine


#endif
