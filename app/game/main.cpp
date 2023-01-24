#include <engine/sample.h>


#include <SDL.h>

#include <cstdio>


int main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    printf("%d\n", foo());
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("SDL_Init failed due to '%s' \n", SDL_GetError());
        exit(1);
    }

    auto window = SDL_CreateWindow(
        "Hello, world!", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        320,
        480,
        SDL_WINDOW_INPUT_GRABBED);

    if (window == nullptr) {
        SDL_Log("Create Window failed with %s\n", SDL_GetError());
        exit(1);
    }
    
    auto renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == nullptr) {
        SDL_Log("SDL_CreateREnderer() failed with %s\n", SDL_GetError());
    }

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

    for (;;) {
        SDL_Event eventum;
        
        while (SDL_PollEvent(&eventum)) {
            if (eventum.type == SDL_QUIT) {
                SDL_Log("Quit message recieved...\n");
                SDL_Quit();
                return 0;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}