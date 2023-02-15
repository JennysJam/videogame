#ifndef GAME_INCLUDE_ENGINE_GRAPHICS_WINDOW_H
#define GAME_INCLUDE_ENGINE_GRAPHICS_WINDOW_H

#include "engine/Option.h"

#include <SDL.h>
#include <SDL_windows.h>
#include <SDL_render.h>


namespace engine {
namespace graphics {

    /// @brief Encapsualt of SDLWindow 
    class Window {
        public:
            Window() noexcept = default;
            ~Window();
            Window(const Window&) = delete;
            Window(SDL_window*, SDL_Renderer*) noexcept;
            Window(Window&& movee) noexcept;
            
            // utility getters/setters
            void set_window_title(const char* name);
            void flip();

            static auto create(int x, int y, int w, int h, Uint32 flags) -> Option<Window>;

        private:
            SDL_Window* _window;
            SDL_Renderer* _renderer;
    };

}
}

#endif