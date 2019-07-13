#pragma once

#include <SDL.h>

// Utility surface manipulation & drawing functions

namespace pong
{

SDL_Surface* ReverseSurface(SDL_Surface* src);

SDL_Surface* DrawCircle(int radius);

}
