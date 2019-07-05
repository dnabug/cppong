#include <iostream>
#include <SDL.h>
#include <stdlib.h>

#include "display.hpp"

namespace pong
{

Display::Display(int w, int h, int m) : width(w), height(h), mspertick(m)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init failed" << std::endl;
        exit(1);
    }

    if (w < 1 || h < 1) {
        std::cerr << "Invalid window dimensions" << std::endl;
        exit(1);
    }

    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Poor Man's Table Tennis: The Video Game");
    SDL_RenderSetLogicalSize(renderer, rwidth, rheight);
}

bool Display::Cycle()
{
    Uint32 start = SDL_GetTicks();

    // TODO: Add logic here

    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) return false;
    }

    Uint32 diff = SDL_GetTicks() - start;
    if (diff < mspertick) SDL_Delay(mspertick - diff);

    return true;
}

Display::~Display()
{
    SDL_Quit();
}

}
